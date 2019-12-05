#include <iostream>
#include "include/Redes.h"

using namespace std;
using namespace Redes;


int main()
{

	DensaGenetica camada1(18, 1, 6, 4);
	vector<int> valores(18, 0);
	int aleatorio = 0;

	for (int n = 0; n < valores.size(); n++)
	{
		aleatorio = rand() % 100;
		valores[n] = aleatorio;
	}
	camada1.aplicarEntrada(valores);
	camada1.calculaSaida();

	for (int s : camada1.obterSaida()) {
		cout << s << "\t";
	}

	int contaMutacao = 100;
	do {
		cout << endl;

		camada1.aplicarEntrada(valores);
		camada1.evoluir();
		camada1.calculaSaida();

		for (int s : camada1.obterSaida()) {
			cout << s << "\t";
		}
		contaMutacao--;
	} while (contaMutacao);


    return 0;
}