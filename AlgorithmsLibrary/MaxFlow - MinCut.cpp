#include <iostream>
#include <map>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;
#define FOR(i, a, b) for( int i = (a); i < (b); i++ )
#define Fore(it, x) for(typeof (x.begin()) it = x.begin(); it != x.end (); it++)
#define Set(a, s) memset(a, s, sizeof (a))
#define LL long long 
#define pii pair<int,int>
#define pll pair<LL,LL>
#define MAX_BOLTS 500
#define MAX_NUTS  500
#define mp make_pair


LL flow[57][57];
//int cost[57][57];
LL G[57][57];
LL oo = 1LL<<62;
bool vis[57];
int p[57];
int n,m;
using namespace std;
#define Set(a, s) memset(a, s, sizeof (a))
bool bfs(int s, int t)
{
	Set(p,-1);
	Set(vis,0);
	vis[s]=1;
	queue<int>Q;
	Q.push(s);
	int c=0;
	while(!Q.empty())
	{
		c=Q.front();Q.pop();
		if(c==t)return 1;
		FOR(i,0,n)
		{
			if(!vis[i] &&  flow[c][i]){	
				p[i]=c;
					Q.push(i);
					vis[i]=1;
				}		
		}
	}
	return 0;
}

int maxFlow(int s ,int t)
{
	LL f;
	LL mf=0;
	while(bfs(s,t))
	{
		f=oo;
		for(int i=t;i!=s;i=p[i])
			f=min(flow[p[i]][i],f);
		for(int i=t;i!=s;i=p[i]){
			flow[p[i]][i]-=f;
			flow[i][p[i]]+=f;
		}
		mf+=f;
	}
	return mf; 
}

void dfs(int u)
{
	vis[u]=1;
	FOR(i,0,n)
		if(!vis[i] && G[u][i] && flow[u][i])
			dfs(i);
}
int main(){
	freopen("input.in","r",stdin);
	while(scanf("%d%d",&n,&m)==2)
	{
		if(n==0 && m==0)break;
		int n1,n2,num;
		Set(G,0);
		Set(flow,0);
		FOR(i,0,m)
		{
			scanf("%d%d%d",&n1,&n2,&num);
			--n1,--n2;
			flow[n1][n2]=flow[n2][n1]=num;			
			G[n1][n2]=G[n2][n1]=1;
		}
		maxFlow(0,1);
		Set(vis,0);
		dfs(0);
		vector<pii > E;
		FOR(i,0,n)
				FOR(j,0,n)
				if(!flow[i][j] && G[i][j] && vis[i]!=vis[j])
					E.push_back(mp(i,j));
		
		FOR(i,0,E.size())
			printf("%d %d\n",E[i].first+1 , E[i].second+1);
		putchar('\n');
	}
	return 0;
}