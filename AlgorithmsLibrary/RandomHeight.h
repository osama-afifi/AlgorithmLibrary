#ifndef SKIP_LIST_RAND
#define SKIP_LIST_RAND
class RandomHeight
{
public:
	RandomHeight(int maxLvl, float prob);
	~RandomHeight() {}
	int newLevel(void);

private:
	int maxLevel;
	float probability;
};
#endif 
