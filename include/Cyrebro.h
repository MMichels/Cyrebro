#include <vector>

#ifndef CYREBRO_H_INCLUDED
#define CYREBRO_H_INCLUDED

using namespace std;

namespace Cyrebro {
    class Neuronio {
    public:
        int qtdLigacoes;
        vector<int> pesos;
        int saida = 0;

        Neuronio();
        Neuronio(int qtdLigacoes);

        void preencherNovosPesos(int qtdLigacoes);

        ~Neuronio();

	private:
		void _inicializarComum();
    };

    class Camada {
    public:
        int qtdNeuronios;
        vector<Neuronio> neuronios;

        Camada();
        Camada(int qtdNeuronios);

        void conectarCamada(Camada* proxCamada);
		void calculaSaida(Camada camadaAnterior);
		void aplicarEntrada(vector<int> valores);

        ~Camada();

    };



}

#endif // CYREBRO_H_INCLUDED
