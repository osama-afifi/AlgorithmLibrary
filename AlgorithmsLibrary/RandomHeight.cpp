#include <stdlib.h>
#include <time.h>

class SkipList
{
private:
	const int maxLvl;
	SkipList(int maxLvl = 10) : maxLvl(maxLvl)
	{
		srand(time(NULL));
	}

	int newLevel()
	{
		int tmpLvl = 1;
		while ((rand()%2==0) && tmpLvl < maxLvl)
			tmpLvl++;
		return tmpLvl;
	}

public:


};