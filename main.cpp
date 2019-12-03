#include <iostream>
#include "include/Redes.h"

using namespace std;
using namespace Redes;


int main()
{

	Densa r(18, 1, 6, 4);
	vector<int> valores(18, 0);
	int aleatorio = 0;

	for (int n = 0; n < valores.size(); n++)
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
	r.aplicarEntrada(valores);
	r.calculaSaida();

	for (int s : r.obterSaida()) {
		cout << s << "\t";
	}


    return 0;
}