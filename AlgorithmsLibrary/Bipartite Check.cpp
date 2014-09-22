#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdio.h>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <stack>

using namespace std;
#define FOR(i, a, b) for( int i = (a); i < (b); i++ )
#define Fore(it, x) for(typeof (x.begin()) it = x.begin(); it != x.end (); it++)
#define Set(a, s) memset(a, s, sizeof (a))
using namespace std;

int oo=1<<25;
int n;
vector< vector<int> > V;
int col[309];
bool isBipartite(int node , int color)
{
	if(col[node]==0)
	{
		col[node]=color;
		bool b=1;
		FOR(i,0,V[node].size())
			b&=isBipartite(V[node][i],color^3);
		return b;
	}
	else if(col[node]==color)return true;
	else return false;
}

int main()
{
	freopen("input.in","r",stdin);	
	char res[][5]={"NO","YES"};
	while(scanf("%d", &n)==1 && n)
	{
		V.clear();
		V.resize(n);
		Set(col,0);
		int n1,n2;
		while(scanf("%d%d",&n1,&n2)==2 && (n1 || n2))
			V[n1-1].push_back(n2-1),V[n2-1].push_back(n1-1);
		printf("%s\n",res[isBipartite(0,1)]);
	}
	return 0;
}
