#include "../include/Ativacoes.h"

namespace Ativacao {
	int relu(int x)
	{
		if (x > 10000) {
			return 10000;
		}
		else if (x < 0) {
			return 0;
		}
		return x;
	}
}
