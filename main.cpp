#include <iostream>
#include "include/Redes.h"

using namespace std;
using namespace Redes;


int main()
{

	Densa cerebro1(18, 1, 6, 4);
	vector<int> valores(18, 0);
	int aleatorio = 0;

	for (int n = 0; n < valores.size(); n++)
	{
		aleatorio = rand() % 100;
		valores[n] = aleatorio;
	}

	cerebro1.aplicarEntrada(valores);
	cerebro1.calculaSaida();

	
	cout << "Saida cerebro1: ";
	for (int s : cerebro1.obterSaida()) {
		cout << s << "\t";
	}
	cout << endl;

	cout << "Realizando mutacoes no cerebro 1: " << endl;;
	int contaMutacao = 1;

	do {
		cout << endl;

		cerebro1.sofrerMutacao();
		cerebro1.aplicarEntrada(valores);
		cerebro1.calculaSaida();

		cout << "Apos " << contaMutacao << " Mutacao: ";
		for (int s : cerebro1.obterSaida()) {
			cout << s << "\t";
		}
		cout << endl;
		contaMutacao++;
	} while (contaMutacao <= 10);


    return 0;
}