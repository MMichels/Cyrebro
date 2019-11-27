#include <cstdlib>
#include <vector>
#include <time.h>
#include "../include/Cyrebro.h"
#include "../include/Ativacoes.h"

using namespace std;

namespace Cyrebro {
    // Classe Neuronio
    Neuronio::Neuronio() {
        this->qtdLigacoes = 0;
		this->_inicializarComum();
    }

    Neuronio::Neuronio(int qtdLigacoes) {
        this->qtdLigacoes = qtdLigacoes;
		this->_inicializarComum();
    }

    void Neuronio::preencherNovosPesos(int qtdLigacoes){
        vector<int>(qtdLigacoes, 0).swap(this->pesos);
		this->qtdLigacoes = qtdLigacoes;
        for(int p = 0; p < qtdLigacoes; p++){
			int negativoPositivo = rand() % 2;
			if (negativoPositivo >= 1) {
				this->pesos[p] = rand() % 1000;
			}
			else {
				this->pesos[p] = - (rand() % 1000);
			}

            
        }
    }

    Neuronio::~Neuronio(){
        vector<int>().swap(this->pesos);
    }

	//private
	void Neuronio::_inicializarComum() {
		this->pesos.reserve(this->qtdLigacoes);
		this->pesos.assign(this->qtdLigacoes, 0);
		srand(time(NULL));
	}



    // Classe Camada
    Camada::Camada(){
        this->qtdNeuronios = 0;
        this->neuronios.reserve(0);
    }

    Camada::Camada(int qtdNeuronios){
        this->qtdNeuronios = qtdNeuronios;
        this->neuronios.reserve(this->qtdNeuronios);
        for(int n = 0; n< this->qtdNeuronios; n++){
            this->neuronios.push_back(Neuronio());
        }
    }


    void Camada::conectarCamada(Camada* proxCamada){
        // Para cada Neuronio da proxima camada (nPC)
        for(int nPC = 0; nPC < proxCamada->qtdNeuronios; nPC ++){
            // Cria um novo vetor de pesos de tamanho igual a quantidade de pesos dessa camada (fully Connected)
            proxCamada->neuronios[nPC].preencherNovosPesos(this->qtdNeuronios);
        }

    }

	void Camada::calculaSaida(Camada camadaAnterior){
		for (int n = 0; n < this->qtdNeuronios; n++) {
			int soma = 0;
			for (int p = 0; p < this->neuronios[n].qtdLigacoes; p++) {
				soma += (camadaAnterior.neuronios[p].saida * this->neuronios[n].pesos[p]);
			}
			this->neuronios[n].saida = Ativacao::relu(soma);
		}

	}

	void Camada::aplicarEntrada(vector<int> valores)
	{
		for (int i = 0; i < this->qtdNeuronios; i++) {
			this->neuronios[i].saida = valores[i];
		}
	}
	

    Camada::~Camada(){
        vector<Neuronio>().swap(this->neuronios);

    }

}
