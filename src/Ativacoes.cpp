#include "../include/Ativacoes.h"

namespace Ativacao {
	int relu(int x)
	{
		if (x > VALOR_TRABALHO) {
			return VALOR_TRABALHO;
		}
		else if (x < 0) {
			return 0;
		}
		return x;
	}
}
