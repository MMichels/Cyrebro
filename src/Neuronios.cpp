#include <time.h>
#include "../include/Neuronios.h"

namespace Neuronios {
	
	void Perceptron::_inicializarComum()
	{
		this->pesos.reserve(this->qtdLigacoes);
		this->pesos.assign(this->qtdLigacoes, 1);
		srand(time(NULL));
	}

	Perceptron::Perceptron()
	{
		this->qtdLigacoes = 0;
		this->_inicializarComum();
	}

	Perceptron::Perceptron(int qtdLigacoes)
	{
		this->qtdLigacoes = qtdLigacoes;
		this->_inicializarComum();
	}

	void Perceptron::randomPesos()
	{
		vector<int> pesos(this->qtdLigacoes, 1);
		this->pesos.swap(pesos);
		for (int p = 0; p < this->qtdLigacoes; p++) {
			int negativoPositivo = rand() % 2;
			if (negativoPositivo >= 1) {
				this->pesos[p] = rand() % 10001;
			}
			else {
				this->pesos[p] = -(rand() % 10001);
			}
		}
	}

	Perceptron::~Perceptron()
	{
		vector<int> vazio(0, 0);
		this->pesos.swap(vazio);
	}
}

