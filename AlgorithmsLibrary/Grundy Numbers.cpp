#include<vector>
#include<set>

using namespace std;

	vector<int>moves;
	
int grundyNumber(int pos) {

	set<int>S;
	for (int i = 0 ; i<moves.size() ; i++) 
	{
		S.insert(pos - moves[i]);
		grundyNumber(pos - moves[i]);
	}
	//return the smallest non-negative integer not in the set s;    
	int ret=0;
	while (S.find(ret)!=S.end()) ret++;
	return ret;
}


int main()
{

}