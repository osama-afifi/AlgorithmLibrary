#include<iostream>
#include<iomanip>
#include<string>
#include<cstring>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<map>
#include<sstream>
#include<queue>
#include<set>
#include<stack>
#include<math.h>

#define FOR(i, a, b) for( int i = (a); i < (b); i++ )
#define  Set(a,b) memset(a,b,sizeof(a))
#define pb push_back
#define mp make_pair
typedef long long LL;

using namespace std;

const int MAX = 209;

int teacher[MAX];
int arr[MAX][MAX];
vector< vector<int> >G;


vector<int> val, num, comp;
int no_vertices, no_components;
stack<int> z;
void dfs(int j, vector<vector<int> > &g) {
    num[j] = val[j] = no_vertices++; comp[j] = 0; z.push(j);
	FOR(i,0,g[j].size())
        if (comp[g[j][i]] == -1) {
            dfs(g[j][i], g);
            num[j] = min(num[j], num[g[j][i]]);
        }
        else if (comp[g[j][i]] == 0)
            num[j] = min(num[j], val[g[j][i]]);

    if (val[j] == num[j]) {
        no_components++;
        while (true) {
            comp[z.top()] = no_components;
            if (z.top() == j) { z.pop(); break; }
            z.pop();
        }
    }
}
vector<int> go(vector<vector<int> > &g) {
    int n = g.size();
    val.assign(n, 0); num = val;
    no_vertices = no_components = 0;
    comp.assign(n, -1);
    FOR(i,0,n) if (comp[i] == -1) dfs(i, g);
    FOR(i,0,n) comp[i]--;
    return comp;
}

__inline int neg(int i)
{
	return i^1;
}

__inline void clause(int a , int b)
{
	G[a^1].push_back(b);
	G[b^1].push_back(a);
}


int n;
void init(int T)
{
	G.clear();
	G.resize(6*n+6);
	FOR(i,0,n)
	{
		FOR(k,0,3)
			FOR(l,0,3)
			if(k!=l && teacher[i]!=k && teacher[i]!=l)
			{
					clause(neg(6*i+2*k),neg(6*i+2*l));	
					clause(6*i+2*k,6*i+2*l);
			}

		FOR(j,T+1,n)
		{
			FOR(k,0,3)
				if(teacher[i]!=k)
				{
					clause(6*i+2*k,6*arr[i][j]+2*k);		
				}
		}
	}

}

int main()
{
	ios_base::sync_with_stdio(0);
	freopen("input.in", "r", stdin);


	while(cin>>n)
	{
		FOR(i,0,n)
			FOR(j,0,n)
		{
			int num;cin>>num;
			if(j)
				arr[i][j]=num-1;
			else
				teacher[i]=num;
		}


		int res=-1;
		int b=0,e=n-1;
		while(b<=e)
		{
			int mid= (b+e)/2;
			init(mid);
			vector<int>V = go(G);
			bool ok=1;
			for(int j = 0 ; j<3*n ; j++)
				if(V[2*j]==V[neg(2*j)])
				{
					ok=0;
					break;
				}
				if(ok)
				{
					res=mid;
					e = mid-1;
				}
				else b = mid+1;

		}
		cout << res <<endl;

	}

	return 0;
}

