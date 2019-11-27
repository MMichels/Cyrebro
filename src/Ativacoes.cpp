#include "../include/Ativacoes.h"

int Ativacao::relu(int x)
{
	if (x > 10000) {
		return 10000;
	}
	else if (x < 0) {
		return 0;
	}
	return x;
}
