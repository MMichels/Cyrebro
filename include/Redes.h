#pragma once
#ifndef REDES_H
#define REDES_H
#include <vector>
#include <math.h>
#include "Camadas.h"

#define DECAIMENTO_MUTACOES 0.999
#define TAXA_MINIMA_MUTACOES 0.15

using namespace std;
using namespace Camadas;

namespace Redes {
	class Densa {
	private:
		void _calcula_tamanho_dna();
		void _calcula_qtd_genes_saida();
		void _inicializarComum();

	public:
		int qtdNeuroniosEntrada, qtdCamadas, profundidadeEscondidas, qtdNeuroniosSaida;
		int tamanhoDNA, qtdGenesCamadaSaida, qtdGenesCamadasEscondidas;
		float qtdMutacoes;

		MLP camadaEntrada;
		vector<MLP> camadasEscondidas;
		MLP camadaSaida;

		Densa();
		Densa(int qtdNeuEntrada, int qtdCamadas, int profundidade, int qtdNeuSaida);

		void aplicarEntrada(vector<int> valoresEntrada);
		void calculaSaida();
		vector<int> obterSaida();

		int mudarValor(int valor);
		vector<int> copiarDNA();
		void colarDNA(vector<int> dna);
		vector<int> alterarDNA(vector<int> dna);
		void sofrerMutacao();

		void copiarRede(Densa* inspiracao);


		~Densa();

	};
}

#endif // !REDES_H

