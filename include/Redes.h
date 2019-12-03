#pragma once
#ifndef REDES_H
#define REDES_H
#include <vector>
#include <math.h>
#include "Camadas.h"


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
}

#endif // !REDES_H

