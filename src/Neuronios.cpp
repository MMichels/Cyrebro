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

	int Perceptron::getQtdLigacoes()
	{
		return this->qtdLigacoes;
	}

	void Perceptron::setQtdLigacoes(int qtdLigacoes)
	{
		this->qtdLigacoes = qtdLigacoes;
	}

	vector<int> Perceptron::getPesos()
	{
		return this->pesos;
	}

	void Perceptron::setPesos(vector<int> novosPesos)
	{
		if (novosPesos.size() == this->getQtdLigacoes()) {
			this->pesos.swap(novosPesos);
		}
		else {
			throw std::exception("O numero de pesos deve ser igual a quantidade de ligações que o neuronio realiza");
		}
	}

	void Perceptron::randomPesos()
	{
		vector<int> pesos(this->qtdLigacoes, 1);
		this->pesos.swap(pesos);
		for (int p = 0; p < this->qtdLigacoes; p++) {
			int negativoPositivo = rand() % 2;
			if (negativoPositivo >= 1) {
				this->pesos[p] = rand() % 1000;
			}
			else {
				this->pesos[p] = -(rand() % 1000);
			}
		}
	}

	int Perceptron::getSaida()
	{
		return this->saida;
	}

	void Perceptron::setSaida(int saida)
	{
		this->saida = saida;
	}

	Perceptron::~Perceptron()
	{
		vector<int> vazio(0, 0);
		this->pesos.swap(vazio);
	}
}

