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
		void _inicializarComum();

	public:
		int qtdNeuroniosEntrada;
		int qtdCamadas;
		int profundidadeEscondidas;
		int qtdNeuroniosSaida;

		MLP camadaEntrada;
		vector<MLP> camadasEscondidas;
		MLP camadaSaida;

		Densa();
		Densa(int qtdNeuEntrada, int qtdCamadas, int profundidade, int qtdNeuSaida);

		void aplicarEntrada(vector<int> valoresEntrada);
		void calculaSaida();
		vector<int> obterSaida();


		~Densa();

	};

	class DensaGenetica : public Densa {
	private:
		void _calcula_tamanho_dna();
		void _calcula_qtd_genes_saida();

	public:
		int tamanhoDNA, qtdGenesCamadaSaida, qtdGenesCamadasEscondidas;
		float qtdMutacoes;

		DensaGenetica(int qtdNeuEntrada, int qtdCamadas, int profundidade, int qtdNeuSaida);

		int mudarValor(int valor);
		void mutacaoCamadasEscondidas(int indiceMutacao);
		void mutacaoCamadaSaida(int indiceMutacao);
		void realizaMutacao(int indiceMutacao);
		void evoluir();

		
	};
}

#endif // !REDES_H

