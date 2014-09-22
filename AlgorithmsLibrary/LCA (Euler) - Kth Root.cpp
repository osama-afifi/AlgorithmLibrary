#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <map>
#include <set>
#include <queue>

using namespace std;
#define FOR(i, a, b) for( int i = (a); i < (b); i++ )
#define Fore(it, x) for(typeof (x.begin()) it = x.begin(); it != x.end (); it++)
#define Set(a, s) memset(a, s, sizeof (a))
#define mp make_pair 
#define MAX 10009 
using namespace std;

int n;
vector<vector< pair<int,int > > > G; 
long long cost[MAX];
int in[MAX];
int d[MAX][25]; // [n][logn]
int L[MAX];
int T[MAX];


void dfs(int node , int l , long long v)
{
	cost[node] = v;
	L[node] = l;
	for(int i = 0 ; i<G[node].size() ; i++)
	{
		T[G[node][i].first] = node;
		dfs(G[node][i].first , l+1 , v+G[node][i].second);
	}
}

void generate(int root)
{
	Set(d,-1);
	dfs(root, 0 , 0);
	T[root]=-1;
	FOR(i,0,n)d[i][0]=T[i];
	for(int j =1  ; (1<<j)<n ; j++)
		FOR(i,0,n)
		if(d[i][j-1]!=-1)
			d[i][j] = d[d[i][j-1]][j-1];
}

int LCA(int x ,int y)
{
	if(L[x]<L[y])swap(x,y);
	int log;
	for(log=1  ; 1<<log <= L[x] ; log++);
	--log;
	for(int i = log ; i>=0 ; i--)
		if(L[x]-(1<<i)>=L[y])
			x = d[x][i];
	if(x==y)return x;
	for(int i = log ; i>=0 ; i--)
		if(d[x][i]!=-1 && d[x][i]!=d[y][i])
			x = d[x][i] , y = d[y][i];
	return T[x];


}

inline int kthAncestor(int x , int k) // gets the kth ancestor of the node
{
	int log;
	for(log=1 ; 1<<log <= L[x]  ; log++);
	log--;
	for(int j = log ; j>=0 ; j--)
		if((1<<j) <= k)
			x = d[x][j]   , k -= (1<<j);
	return x;
}

int getKth(int p, int q, int k, int LCA) {
	int d,log,i;
	if(LCA == p) {
		d = L[q] - L[p] + 1;
		swap(p,q);
		k = d - k + 1;
	}
	else if(LCA != q)

		if(L[p] - L[LCA] + 1 < k) {
			d = L[p] + L[q] - 2 * L[LCA] + 1;
			k = d - k + 1;
			swap(p,q);
		}
	
	for(log=1;(1<<log)<=L[p];log++);
	log--;
	k--;
	for(i=log;i>=0;i--)
		if((1<<i) <= k) 
		p = d[p][i] , 	k -= (1<<i);
	
	return p;
}

int main()
{
	freopen("input.in","r",stdin);
	int t,kase=0;
	scanf("%d" , &t);

	while(t--)
	{
		G.clear();
		Set(in,0);
		scanf("%d" , &n);
		G.resize(n+1);
		int root=0;
		int a,b,c;


		FOR(i,0,n-1)
		{
			scanf("%d %d %d" , &a , &b , &c);
			--a ,--b;
			G[a].push_back(make_pair(b, c));
			in[b]++ ;
		}
		FOR(i,0,n) 
			if(!in[i]) {root=i;break;} ;

		generate(root);
		char text[5];

		while(scanf("%s",&text)==1)
		{
			if(text[1]=='O')break;
			else if(text[1]=='I')
			{
				scanf("%d %d" , &a , &b);
				--a , --b;
				int lca = LCA(a,b);
				long long  dist = 0 ;
				if(lca == a || lca == b)
					dist = abs(cost[a]-cost[b]);
				else 
					dist = cost[a] + cost[b] - 2*cost[lca];
				printf("%lld\n",dist);
			}
			else if(text[1]=='T')
			{
				scanf("%d %d %d" , &a , &b , &c);
				--a , --b;
				int lca = LCA(a,b);

				int kth = getKth(a,b,c,lca);
				printf("%d\n",kth+1);
			}

		}
		puts("");
	}


	return 0;
}