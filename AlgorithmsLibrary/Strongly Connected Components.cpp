
#include <iostream>
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

#define MAX 100009

int n,m,SCC;
vector< vector<int> >V;

int zatouna=0;
int nodelow[MAX];
int nodeindex[MAX];
bool vis[MAX];
int component[MAX];
int degree[MAX];
stack<int>S;

void tarjanSCC(int cur)
{
	nodeindex[cur]=nodelow[cur]=zatouna++;
	vis[cur]=1;
	S.push(cur);
	FOR(i,0,V[cur].size())
	{
		int v=V[cur][i];
		if(nodeindex[v]==-1)
			tarjanSCC(v);
		if(vis[v])
			nodelow[cur]=min(nodelow[cur],nodelow[v]);
	}

	if(nodeindex[cur]==nodelow[cur]) //SCC Root Found
	{
		while(1)
		{
			int v=S.top();
			component[v]=SCC;
			vis[v]=0;
			S.pop();			
			if(v==cur)break;
		}
		SCC++;
	}

}

int main()
{
	freopen("input.in","r",stdin);


	while(scanf("%d%d",&n,&m)==2)
	{
		if(!n && !m)break;

		Set(degree,0);
		zatouna=SCC=0;
		V.clear();
		V.resize(n+2);
		int n1,n2;
		while(!S.empty())S.pop();
		Set(vis,0);
		Set(nodelow,0);
		Set(nodeindex,-1);

		// Graph Input below
	}
	return 0;
}

