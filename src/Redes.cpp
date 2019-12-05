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
	
	void DensaGenetica::_calcula_tamanho_dna()
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

	void DensaGenetica::_calcula_qtd_genes_saida()
	{
		this->qtdGenesCamadaSaida = 0;
		for (Perceptron p : this->camadaSaida.perceptrons) {
			this->qtdGenesCamadaSaida += p.qtdLigacoes;
		}
		this->qtdGenesCamadasEscondidas = this->tamanhoDNA - this->qtdGenesCamadaSaida;
	}

	DensaGenetica::DensaGenetica(int qtdNeuEntrada, int qtdCamadas, int profundidade, int qtdNeuSaida) : Densa(qtdNeuEntrada, qtdCamadas, profundidade, qtdNeuSaida)
	{
		this->_calcula_tamanho_dna();
		this->_calcula_qtd_genes_saida();		
		this->qtdMutacoes = (double)this->tamanhoDNA;
	}

	int DensaGenetica::mudarValor(int valor)
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
	
	void DensaGenetica::mutacaoCamadasEscondidas(int indiceMutacao)
	{
		int contador = 0, indicePeso = -1, indiceCamada = -1, indicePerceptron = -1, valor = 0;

		MLP* camadaEscondida;
		Perceptron* perceptron = new Perceptron();

		for (indiceCamada = 0; indiceCamada < this->qtdCamadas; indiceCamada++) {
			camadaEscondida = &this->camadasEscondidas[indiceCamada];
			for (indicePerceptron = 0; indicePerceptron < camadaEscondida->qtdPerceptrons; indicePerceptron++) {
				perceptron = &camadaEscondida->perceptrons[indicePerceptron];
				if (perceptron->qtdLigacoes + contador >= indiceMutacao) {
					indicePeso = indiceMutacao - contador;
					break;
				}
				else {
					contador += perceptron->qtdLigacoes;
				}
			}
			if (indicePeso > -1) {
				break;
			}
		}

		if (indicePeso == -1) {
			//	Se ocorrer algum erro no calculo do peso...
			indicePeso = rand() % perceptron->qtdLigacoes;
		}

		//	Como a variavel perceptron é um ponteiro, nao é necessario realizar o set do perceptron na camada
		valor = perceptron->pesos[indicePeso-1];
		valor = this->mudarValor(valor);
		//perceptron->pesos[indicePeso-1] = valor;
		this->camadasEscondidas[indiceCamada].perceptrons[indicePerceptron].pesos[indicePeso - 1] = valor;
	}
	
	void DensaGenetica::mutacaoCamadaSaida(int indiceMutacao)
	{
		indiceMutacao -= this->qtdGenesCamadasEscondidas;
		int contador = 0, indicePerceptron = -1, indicePeso = -1, valor=0;

		Perceptron* perceptron = new Perceptron();
		for (indicePerceptron = 0; indicePerceptron < this->qtdNeuroniosSaida; indicePerceptron++) {
			perceptron = &this->camadaSaida.perceptrons[indicePerceptron];
			if (perceptron->qtdLigacoes + contador >= indiceMutacao) {
				indicePeso = indiceMutacao - contador;
				break;
			} else {
				contador += perceptron->qtdLigacoes;
			}
		}

		valor = perceptron->pesos[indicePeso-1];
		valor = this->mudarValor(valor);
		this->camadaSaida.perceptrons[indicePerceptron].pesos[indicePeso - 1] = valor;
	}

	void DensaGenetica::realizaMutacao(int indiceMutacao)
	{
		if (indiceMutacao <= this->qtdGenesCamadasEscondidas) {
			this->mutacaoCamadasEscondidas(indiceMutacao);
		}
		else {
			this->mutacaoCamadaSaida(indiceMutacao);
		}
	}

	void DensaGenetica::evoluir()
	{
		int mutacoes = rand() % (int) this->qtdMutacoes;
		int indiceMutacao = rand() % this->tamanhoDNA;
		while (mutacoes >= 0) {
			this->realizaMutacao(indiceMutacao);
			indiceMutacao = rand() % this->tamanhoDNA;
			mutacoes--;
		}

		this->qtdMutacoes *= DECAIMENTO_MUTACOES;
		if (this->qtdMutacoes > (this->tamanhoDNA * TAXA_MINIMA_MUTACOES)) {
			this->qtdMutacoes *= DECAIMENTO_MUTACOES;
		}

	}
}
