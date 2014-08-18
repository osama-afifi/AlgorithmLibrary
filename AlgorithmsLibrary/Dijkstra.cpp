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
#define ALL(A) A.begin(), A.end()
#define Set(a, s) memset(a, s, sizeof (a))
#define pb push_back
#define mp make_pair
typedef long long LL;
using namespace std;


struct node
{
	int v;
	LL c;
	bool operator < (const node &p)const
	{
		return p.c<c;
	}
	node(int v, int c) : v(v), c(c)
	{}
};

LL n,m,k;
const int MAX=100000;
LL d[MAX+7];
LL R[MAX+7];
LL RFreq[MAX+7];
LL relaxFreq[MAX+7];

vector< vector<node> > A;


void dijkstra(int s)
{
	FOR(i,0,n+1)
		d[i]=1LL<<50;
	Set(relaxFreq,0);
	node b(s,0);
	priority_queue<node>PQ;
	PQ.push(b);

	while(PQ.size())
	{
		node cur  = PQ.top();
		PQ.pop();
		if(cur.c==d[cur.v])
			relaxFreq[cur.v]++;
		if(cur.c>=d[cur.v])
			continue;
		relaxFreq[cur.v]=1;
		d[cur.v] = cur.c;
		FOR(i,0,A[cur.v].size())
		{
			int next=A[cur.v][i].v;
			LL cost = cur.c+A[cur.v][i].c;
			 if(d[next]>=cost)
				PQ.push(node(next,cost));
		}
	}

}

int main()
{
	freopen("input.in", "r" , stdin);

	while(cin>>n>>m>>k)
	{
		A.clear();
		A.resize(n+1);
		Set(R,0);
		Set(RFreq,0);
		LL a,b,c;
		FOR(i,0,m)
		{
			
			cin>>a>>b>>c;
			A[a].push_back(node(b,c));
			A[b].push_back(node(a,c));
		}

		FOR(i,0,k)
		{
		
			cin>>a>>c;
			RFreq[a]++;
			if(R[a])
				R[a]=min(R[a],c);
			else R[a]=c;

		}
		FOR(i,1,n+1)
			if(RFreq[i])
			{
				A[1].push_back(node(i,R[i]));
				A[i].push_back(node(1,R[i]));
			}
			dijkstra(1);
			int res=0;
			FOR(i,1,n+1)
				if(RFreq[i] && (R[i]>d[i] || (R[i]>=d[i] && relaxFreq[i]>1) ))
					res++;
			FOR(i,1,n+1)
				if(RFreq[i]>1)
					res+=RFreq[i]-1;

			cout << res << endl;
	}

	return 0;
}