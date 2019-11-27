#include "../include/Neuronios.h"
#include "../include/Ativacoes.h"
#include "../include/Camadas.h"

using namespace Neuronios;

namespace Camadas {
	void MLP::_inicializadorPadrao()
	{
		vector<Perceptron> p(this->qtdPerceptrons, Perceptron());
		this->perceptrons.swap(p);
	}

	MLP::MLP()
	{
		this->qtdPerceptrons = 0;
		this->_inicializadorPadrao();
	}

	MLP::MLP(int qtdPerceptrons)
	{
		this->qtdPerceptrons = qtdPerceptrons;
		this->_inicializadorPadrao();
	}

	int MLP::getQtdPerceptrons()
	{
		return this->qtdPerceptrons;
	}

	void MLP::setQtdPerceptrons(int qtdPerceptrons)
	{
		this->qtdPerceptrons = qtdPerceptrons;
	}

	vector<Perceptron> MLP::getPerceptrons()
	{
		return this->perceptrons;
	}

	void MLP::setPerceptrons(vector<Perceptron> novosPerceptrons)
	{
		if (novosPerceptrons.size() == this->qtdPerceptrons) {
			this->perceptrons.swap(novosPerceptrons);
		}
		else {
			throw std::exception("O tamanho do vetor com os novos Perceptrons deve ser \
igual a quantidade de neuronios da camada, considere alterar a quantidade de neuronios ou o tamanho do vetor");

		}
	}

	void MLP::conectarProxCamada(MLP* proxCamada)
	{
		// Para cada Neuronio da proxima camada (nPC)
		for (int nPC = 0; nPC < proxCamada->qtdPerceptrons; nPC++) {
			// Cria um novo vetor de pesos de tamanho igual a quantidade de pesos dessa camada (fully Connected)
			proxCamada->perceptrons[nPC].setQtdLigacoes(this->qtdPerceptrons);
			proxCamada->perceptrons[nPC].randomPesos();
		}
	}

	void MLP::calculaSaida(MLP* camadaAnterior)
	{
		for (int n = 0; n < this->qtdPerceptrons; n++) {
			int soma = 0;
			vector<int> pesosPerceptron = this->perceptrons[n].getPesos();
			for (int p = 0; p < this->perceptrons[n].getQtdLigacoes(); p++) {
				soma += (camadaAnterior->perceptrons[p].getSaida() * pesosPerceptron[p]);
			}
			this->perceptrons[n].setSaida(Ativacao::relu(soma));
		}
	}

	void MLP::aplicarEntrada(vector<int> valoresEntrada)
	{
		for (int i = 0; i < this->qtdPerceptrons; i++) {
			this->perceptrons[i].setSaida(valoresEntrada[i]);
		}
	}

	MLP::~MLP()
	{
		vector<Perceptron>().swap(this->perceptrons);
	}



}