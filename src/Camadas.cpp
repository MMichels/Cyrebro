#include "../include/Neuronios.h"
#include "../include/Ativacoes.h"
#include "../include/Camadas.h"
#include <cmath>


using namespace Neuronios;

namespace Camadas {
	void MLP::_inicializadorPadrao()
	{
		vector<Perceptron> p(this->qtdPerceptrons, Perceptron());
		this->perceptrons.swap(p);
	}

	MLP::MLP()
	{
		this->qtdPerceptrons = 0 + BIAS;
		this->_inicializadorPadrao();
	}

	MLP::MLP(int qtdPerceptrons)
	{
		this->qtdPerceptrons = qtdPerceptrons + BIAS;
		this->_inicializadorPadrao();
	}

	void MLP::conectarProxCamada(MLP* proxCamada)
	{
		// Para cada Neuronio da proxima camada (nPC)
		for (int nPC = 0; nPC < proxCamada->qtdPerceptrons; nPC++) {
			// Cria um novo vetor de pesos de tamanho igual a quantidade de pesos dessa camada (fully Connected)
			proxCamada->perceptrons[nPC].qtdLigacoes = this->qtdPerceptrons;
			proxCamada->perceptrons[nPC].randomPesos();
		}
	}

	void MLP::calculaSaida(MLP* camadaAnterior)
	{
		for (int n = 0; n < this->qtdPerceptrons - BIAS; n++) {
			int soma = 0;
			vector<int> pesosPerceptron = this->perceptrons[n].pesos;
			for (int p = 0; p < this->perceptrons[n].qtdLigacoes; p++) {
				soma += (camadaAnterior->perceptrons[p].saida * pesosPerceptron[p]);
			}
			this->perceptrons[n].saida = Ativacao::relu(soma);
		}
	}

	vector<int> MLP::obterSaida()
	{
		vector<int> saida;
		for( int p = 0; p < this->qtdPerceptrons - BIAS; p++){
			saida.push_back(this->perceptrons[p].saida);
		}
		return saida;
	}

	void MLP::aplicarEntrada(vector<int> valoresEntrada)
	{
		for (int i = 0; i < this->qtdPerceptrons; i++) {
			this->perceptrons[i].saida = valoresEntrada[i];
		}
	}
	
	MLP::~MLP()
	{
		vector<Perceptron>().swap(this->perceptrons);
	}



}