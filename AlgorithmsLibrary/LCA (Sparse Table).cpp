#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <math.h>
#include <set>
#include <queue>

using namespace std;
#define for(i, a, b) for( int i = (a); i < (b); i++ )
#define fore(it, x) for(typeof (x.begin()) it = x.begin(); it != x.end (); it++)
#define set(a, s) memset(a, s, sizeof (a))
#define mp make_pair 
#define maxn 1009 
using namespace std;

int d[maxn][20]; // [n][logn]
int l[maxn];
int t[maxn];
int n;
vector< vector<int > > g;
void dfs(int node , int l)
{
	l[node] = l;
	for(int i = 0 ; i<g[node].size() ; i++)
	{
		t[g[node][i]] = node;
		dfs(g[node][i] , l+1);
	}
}


inline void generate(int root)
{
	dfs(root,0);
	t[root]=-1;
	set(d,-1);
	for(i,0,n)
		d[i][0] = t[i];

	for(int  j = 1 ; 1<<j < n ; j++)
		for(i,0,n)
		if(d[i][j-1]!=-1)
			d[i][j]  = d[d[i][j-1]][j-1];

}

inline int lca(int x , int y)
{
	if(l[x]<l[y])
		swap(x,y);
	int log , j;
	for(log=1 ; 1<<log <= l[x]  ; log++);
	log--;

	for(j = log ; j>=0 ; j--)
		if(l[x]- (1<<j) >=l[y])
			x = d[x][j];
	if(x==y)return x;
	for(j = log ; j>=0 ; j--)
		if(d[x][j]!=-1  && d[y][j]!=-1  && d[x][j]!=d[y][j])
			x = d[x][j] , y = d[y][j];
	return t[x];
}




int in[maxn];
int main()
{
	freopen("input.in","r",stdin);
	int t,kase=0;
	scanf("%d" , &t);

	while(t--)
	{
		g.clear();
		set(in,0);
		scanf("%d" , &n);
		g.resize(n+1);
		int root=0;
		for(i,0,n)
		{
			int c,num;
			scanf("%d" , &c);
			while(c--)
			{
				scanf("%d" , &num);
				--num;
				g[i].push_back(num);
				++in[num] ;
			}
			for(i,0,n) 
				if(!in[i]) {root=i;break;} ;

		}
		generate(root);
		printf("case %d:\n" , ++kase);
		int k;
		scanf("%d" , &k);
		while(k--)
		{
			int a,b;
			scanf("%d %d" , &a , &b);
			--a , --b;
			printf("%d\n",lca(a,b)+1);
		}
	}

}