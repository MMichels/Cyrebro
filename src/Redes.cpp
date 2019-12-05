#pragma once
#include <vector>
#include "../include/Util.h"
#include "../include/Neuronios.h"
#include "../include/Camadas.h"
#include "../include/Redes.h"

namespace Redes {
	void Densa::_inicializarComum() {
		this->camadaEntrada = MLP(this->qtdNeuroniosEntrada);
		this->camadasEscondidas = vector<MLP>(this->qtdCamadas, MLP(this->profundidadeEscondidas));
		this->camadaSaida = MLP(this->qtdNeuroniosSaida);

		if (this->qtdCamadas >= 1) {
			this->camadaEntrada.conectarProxCamada(&this->camadasEscondidas[0]);
			for (int i = 1; i < this->qtdCamadas; i++) {
				this->camadasEscondidas[(int) i - 1].conectarProxCamada(&this->camadasEscondidas[i]);
			}
			this->camadasEscondidas[(int)this->qtdCamadas - 1].conectarProxCamada(&this->camadaSaida);
		}
		else {
			this->camadaEntrada.conectarProxCamada(&this->camadaSaida);
		}
		this->_calcula_tamanho_dna();
		this->_calcula_qtd_genes_saida();
		this->qtdMutacoes = this->tamanhoDNA;
	}
	
	Densa::Densa() {
		this->qtdNeuroniosEntrada = 0;
		this->qtdCamadas = 0;
		this->profundidadeEscondidas = 0;
		this->qtdNeuroniosSaida = 0;
		this->_inicializarComum();
	}

	Densa::Densa(int qtdNeuEntrada, int qtdCamadas, int profundidade, int qtdNeuSaida) {
		this->qtdNeuroniosEntrada = qtdNeuEntrada;
		this->qtdCamadas = qtdCamadas;
		this->profundidadeEscondidas = profundidade;
		this->qtdNeuroniosSaida = qtdNeuSaida;
		this->_inicializarComum();
	}
	   
	void Densa::aplicarEntrada(vector<int> valoresEntrada)	{
		
		for (int i = 0; i < this->qtdNeuroniosEntrada; i++) {
			this->camadaEntrada.perceptrons[i].saida = valoresEntrada[i];
			i++;
		}
	}

	void Densa::calculaSaida()	{
		// Saida camada escondida 1
		if (this->qtdCamadas >= 1) {
			this->camadasEscondidas[0].calculaSaida(&this->camadaEntrada);

			for (int i = 1; i < this->qtdCamadas; i++) {
				this->camadasEscondidas[i].calculaSaida(&this->camadasEscondidas[(int) i - 1]);
			}

			this->camadaSaida.calculaSaida(&this->camadasEscondidas[(int)this->qtdCamadas - 1]);
		}
		else {
			this->camadaSaida.calculaSaida(&this->camadaEntrada);
		}
	}

	vector<int> Densa::obterSaida()	{
		return this->camadaSaida.obterSaida();
	}
	
	Densa::~Densa()
	{
		this->camadaEntrada = MLP(0);
		vector<MLP>().swap(this->camadasEscondidas);
		this->camadaSaida = MLP(0);
	}
	
	
	//	Rede Genética
	
	void Densa::_calcula_tamanho_dna()
	{
		this->tamanhoDNA = 0;
		for (MLP c : this->camadasEscondidas) {
			for (Perceptron p : c.perceptrons) {
				this->tamanhoDNA += p.qtdLigacoes;
			}
		}
		for (Perceptron p : this->camadaSaida.perceptrons) {
			this->tamanhoDNA += p.qtdLigacoes;
		}
	}

	void Densa::_calcula_qtd_genes_saida()
	{
		this->qtdGenesCamadaSaida = 0;
		for (Perceptron p : this->camadaSaida.perceptrons) {
			this->qtdGenesCamadaSaida += p.qtdLigacoes;
		}
		this->qtdGenesCamadasEscondidas = this->tamanhoDNA - this->qtdGenesCamadaSaida;
	}

	int Densa::mudarValor(int valor)
	{
		int tipoMutacao = rand() % 3;
		int numero = 0;
		switch (tipoMutacao)
		{
		case 0:
			valor = Cyrebro::getRandomValue();
			break;
		case 1:
			numero = (rand() % VALOR_TRABALHO + 1) / VALOR_TRABALHO + 0.5;
			valor *= numero;
			break;
		case 2:
			numero = Cyrebro::getRandomValue()/100.0;
			valor += numero;
			break;
		default:
			break;
		}

		return valor;
	}

	vector<int> Densa::copiarDNA()
	{
		vector<int> DNA;
		vector<MLP> todasCamadas = this->camadasEscondidas;
		todasCamadas.push_back(this->camadaSaida);
		for (MLP c : todasCamadas) {
			for (Perceptron p : c.perceptrons) {
				for (int peso : p.pesos) {
					DNA.push_back(peso);
				}
			}
		}
		return DNA;
	}

	void Densa::colarDNA(vector<int> dna)
	{
		vector<MLP> todasCamadas = this->camadasEscondidas;
		todasCamadas.push_back(this->camadaSaida);
		int contador = 0;
		
		for (int c = 0; c < todasCamadas.size(); c++) {
			MLP* camada = &todasCamadas[c];
			for (int pc = 0; pc < camada->qtdPerceptrons; pc++) {
				Perceptron* perceptron = &camada->perceptrons[pc];
				for (int ps = 0; ps < perceptron->qtdLigacoes; ps++) {
					perceptron->pesos[ps] = dna[contador];
					contador++;
				}
			}
			if (c < this->qtdCamadas) {
				this->camadasEscondidas[c] = todasCamadas[c];
			}
			else if (c == this->qtdCamadas) {
				this->camadaSaida = todasCamadas[c];
			}

		}

	}

	vector<int> Densa::alterarDNA(vector<int> dna)
	{
		int mutacoes = rand() % (int) this->qtdMutacoes;
		int indiceMutacao = rand() % dna.size();
		int valor = Cyrebro::getRandomValue();
		do {
			valor = dna[indiceMutacao];
			valor = this->mudarValor(valor);
			dna[indiceMutacao] = valor;
			indiceMutacao = rand() % dna.size();
			mutacoes--;
		} while (mutacoes);
		return dna;
	}

	void Densa::sofrerMutacao()
	{
		vector<int> dna = this->copiarDNA();
		dna = this->alterarDNA(dna);
		this->colarDNA(dna);

		if (this->qtdMutacoes > (this->qtdMutacoes * TAXA_MINIMA_MUTACOES)) {
			this->qtdMutacoes *= DECAIMENTO_MUTACOES;
		}
	}
	
	void Densa::copiarRede(Densa*inspiracao)
	{
		vector<int> dnaInpiracao = inspiracao->copiarDNA();
		this->colarDNA(dnaInpiracao);
	}
}
