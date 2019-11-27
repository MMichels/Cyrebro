#include <iostream>
#include "include/Cyrebro.h"

using namespace std;
using namespace Cyrebro;


void testeCriacaoNeuronio();

void testeCriacaoCamada();

int main()
{
    Camada c1(5), c2(3);

    c1.conectarCamada(&c2);

	vector<int> valores(5);
	int aleatorio = 0;

	for (int n = 0; n < c1.qtdNeuronios; n++)
	{
		aleatorio = rand() % 3;
		switch (aleatorio)
		{
		case 1:
			valores[n] = rand() % 10000;
			break;
		case 2:
			valores[n] = 10000;
			break;
		default:
			valores[n] = 0;
		}

	}
	c1.aplicarEntrada(valores);

	c2.calculaSaida(c1);

	for (Neuronio n : c2.neuronios) {
		cout << n.saida << endl;
	}

    return 0;
}


void testeCriacaoNeuronio(){
    int qtdLigacoes = 0;

    cout << "Digite a quantidade de ligações: " << endl;
    cin >> qtdLigacoes;

    cout << "Criando neuronio..." << endl;

    Neuronio n(qtdLigacoes);

    cout << "Neuronio criado..." << endl;
    cout << "Pesos do neuronio:" << endl;
    for(int p = 0; p < n.qtdLigacoes; p++){
        cout << n.pesos[p] << endl;
    }
}


void testeCriacaoCamada(){
    int qtdNeuronios = 8;

    cout << "Digite a quantidade de neuronios: " << endl;
    cin >> qtdNeuronios;

    cout << "Criando camada..." << endl;

    Camada c(qtdNeuronios);

    cout << "Camada criada..." << endl;
    cout << "Pesos do 1° neuronio:" << endl;

    Neuronio n = c.neuronios[0];

    for(int p = 0; p < n.qtdLigacoes; p++){
        cout << n.pesos[p] << endl;
    }


}
