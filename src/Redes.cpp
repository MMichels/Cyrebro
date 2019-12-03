#pragma once
#include <vector>
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
				this->camadasEscondidas[i - 1].conectarProxCamada(&this->camadasEscondidas[i]);
			}
			this->camadasEscondidas[this->qtdCamadas-1].conectarProxCamada(&this->camadaSaida);
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
				this->camadasEscondidas[i].calculaSaida(&this->camadasEscondidas[i - 1]);
			}

			this->camadaSaida.calculaSaida(&this->camadasEscondidas[this->qtdCamadas - 1]);
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
}
