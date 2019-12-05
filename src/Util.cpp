#include <cstdlib>

namespace Cyrebro {
	double getRandomValue()
	{
		return (rand() % 20001 / 10.0) - 1000.0;
		//return (rand()%201/10.0) - 10.0;
		//return (rand()%2001/1000.0) - 1.0;
		//return (rand()%2001/10000.0) - 0.1;

		//return rand()%3 - 1;
	}
}