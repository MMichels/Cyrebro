#pragma once
#ifndef NEURONIOS_H
#define NEURONIOS_H
#include <vector>

#ifndef VALOR_TRABALHO
#define VALOR_TRABALHO 10000
#endif // !VALOR_TRABALHO

using namespace std;

namespace Neuronios {
	class Perceptron {

	public:
		int qtdLigacoes = 0, saida = 1;

		vector<int> pesos;

		// Possui a inicizalizacao comum dos neuronios perceptrons.
		void _inicializarComum();


		// Construtor padrão, inicializa um neuronio sem pesos e sem ligacoes
		Perceptron();

		/**
			Inicializa um Perceptron com a quantidade desejada de ligacoes e o 
			vetor de pesos das ligacoes preenchido de zeros

			@param qtdLigacoes: Numero de ligacoes que o Perceptron realiza, tambem
				é o tamanho do vetor de pesos.		 
		*/
		Perceptron(int qtdLigacoes);

		/*
			Cria um vetor de inteiros com tamanho igual a quantidade de ligacoes
			utiliza esse novo vetor como vetor de pesos e em seguida, randomiza
			os valores do vetor de pesos
		*/
		void randomPesos();

		/**
			Altera o valor da saida do neuronio.

			@param saida: novo valor de saida.
		*/

		//	Desconstrutor padrão.
		~Perceptron();


	};
}


#endif