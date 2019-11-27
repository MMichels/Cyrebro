#pragma once
#ifndef CAMADAS_H
#define CAMADAS_H
#include <vector>
#include "Neuronios.h"
#include "Ativacoes.h"

using namespace Neuronios;

namespace Camadas {
	class MLP {
	private:
		int qtdPerceptrons; // Quantidade de Neuronios da camada
		vector<Perceptron> perceptrons; // Vetor com os Neuronios do tipo Perceptron.
		void _inicializadorPadrao();
	public:
		//	Construtor Padrão
		MLP();

		/*
			Instancia a Camada com a quantidade de neuronios desejada, mas os neuronios não
			possuem vetor de pesos nem a quantidade de ligacoes que realiza

			@param qtdPerceptrons: Numero de neuronios da camada
		*/
		MLP(int qtdPerceptrons);

		//	Retorna a quantidade de neuronios da camada
		int getQtdPerceptrons();
		/*	
			Altera a quantidade de neuronios da camada

			@param qtdPerceptrons: Nova quantidade de neuronios da rede.
		*/
		void setQtdPerceptrons(int qtdPerceptrons);

		// Retorna o vetor com os neuronios da camada.
		vector<Perceptron> getPerceptrons();
		/*
			Substitui os Neuronios da camada, em caso de adicionar mais neuronios a camada,
			é necessario alterar a quantidade de neuronios da rede antes de adicionar os neuronios
			novos.

			@param novosPerceptrons: Vetor contendo os novos neuronios da camada
		*/
		void setPerceptrons(vector<Perceptron> novosPerceptrons);


		/*
			Conecta as camadas, durante a conexão, os neuronios da proxima camada
			recebem o numero de conexões que iram realizar, e o vetor de pesos de cada
			neurónio é inicializado com valores aleatórios.

			o vetor de pesos é iniciado nos vetores da camada seguinte para manter a
			consistencia do somatório ao calcular a saida de cada neuronio (vide função calcSaida())

			@param proxCamada: Proxima camada da Rede, na qual essa camada será conectada
		*/
		void conectarProxCamada(MLP* proxCamada);

		/*
			Realiza o somatório e calculo da saida de cada neuronio da camada de acordo com
			o valor de saida dos neuronios da camada anterior, respeitando a formula de somátório 
			basica dos neuronios do tipo perceptron, com ativação do tipo relu.

			@return Vetor com o valor de saida de cada neuronio da rede.
		*/
		void calculaSaida(MLP* camadaAnterior);

		/*
			Aplica os valores de entrada recebidos na saida de cada neuronio da camada.

			@param valoresEntrada: Vetor de inteiros contendo os valores que serão aplicados nas saidas
				dos neuronios na rede, o tamanho desse vetor deve ser igual a quantidade de neuronios da camada.
		*/
		void aplicarEntrada(vector<int> valoresEntrada);

		// Desconstrutor padrão.
		~MLP();

	};
}


#endif // CAMADAS_H
