#pragma once
#ifndef NEURONIOS_H
#define NEURONIOS_H

#include <vector>

using namespace std;

namespace Neuronios {
	class Perceptron {
	private:
		int qtdLigacoes = 0;
		vector<int> pesos;
		int saida = 1;

		// Possui a inicizalizacao comum dos neuronios perceptrons.
		void _inicializarComum();

	public:

		// Construtor padrão, inicializa um neuronio sem pesos e sem ligacoes
		Perceptron();

		/**
			Inicializa um Perceptron com a quantidade desejada de ligacoes e o 
			vetor de pesos das ligacoes preenchido de zeros

			@param qtdLigacoes: Numero de ligacoes que o Perceptron realiza, tambem
				é o tamanho do vetor de pesos.		 
		*/
		Perceptron(int qtdLigacoes);

		// Retorna o numero de ligacoes que o perceptron realiza
		int getQtdLigacoes();

		/*	Altera o numero de ligacoes que o perceptron realiza
			@param qtdLigacoes: Novo numero de ligacoes.
		*/
		void setQtdLigacoes(int qtdLigacoes);
		
		//	Retorna o vetor de pesos do neuronio
		vector<int> getPesos();

		/*
			Altera o vetor de pesos do neuronio, o novo vetor de pesos deve ter 
			tamanho igual a variavel qtdLigacoes.

			@param novosPesos: Vetor com os novos pesos do Perceptron
		*/
		void setPesos(vector<int> novosPesos);

		/*
			Cria um vetor de inteiros com tamanho igual a quantidade de ligacoes
			utiliza esse novo vetor como vetor de pesos e em seguida, randomiza
			os valores do vetor de pesos
		*/
		void randomPesos();

		//	Retorna o valor da saida do neuronio.
		int getSaida();

		/**
			Altera o valor da saida do neuronio.

			@param saida: novo valor de saida.S
		*/
		void setSaida(int saida);

		//	Desconstrutor padrão.
		~Perceptron();


	};
}


#endif