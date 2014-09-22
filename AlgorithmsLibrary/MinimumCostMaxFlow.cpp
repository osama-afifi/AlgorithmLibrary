// Not Ac

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdio.h>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <map>
#include <queue>

using namespace std;
#define FOR(i, a, b) for( int i = (a); i < (b); i++ )
#define Fore(it, x) for(typeof (x.begin()) it = x.begin(); it != x.end (); it++)
#define Set(a, s) memset(a, s, sizeof (a))
#define mp make_pair
#define in(k) (int)k*2
#define out(k) (int)k*2+1
using namespace std;

//Min Cost Max Flow 
//Add edges with –ve cost if max cost is required 

int const oo = 1e9;
int n,m; 
struct Edge 
{ 
	int fr,to;
	int cost,flow;
	Edge(){fr=to=cost=flow=-1;} 
	Edge(int a,int b,int c,int d) 
		: fr(a),to(b),cost(c),flow(d) 
	{ } 
}; 
struct MinCostMaxFlow 
{ 
	vector<Edge> E; 
	int flow[415]; 
	int cost[415]; 
	int path[415]; 

	void AddEdge(int fr,int to,double co,double fl) 
	{ 
		E.push_back(Edge(fr,to,co,fl));
		E.push_back(Edge(to,fr,-co,0));
	} 
	MinCostMaxFlow() 
	{ clear(); } 

	void getPath(int src, int snk) {
		memset(flow , 0, sizeof flow);
		memset(path , -1, sizeof path);
		fill(cost , cost+205 , 1e7);
		flow[src] = oo;
		cost[src] = 0.0;
		for(int i = 0; i<n-1; i++) {
			bool relaxed = 0;
			for(int j = 0; j< E.size(); j++) {
				Edge &e = E[j];
				if(e.flow && cost[e.fr]+e.cost<cost[e.to]  ) {
					cost[e.to] = cost[e.fr]+e.cost;
					relaxed = true;
					path[e.to] = j;
					flow[e.to] = min(flow[e.fr] , e.flow);
				}
			}
			if(!relaxed) break;

		}
	}
	pair<int,int> MCMF(int src,int sink)  // flow-cost
	{ 
		if(src == sink) 
			return make_pair(oo,0.0); 
		int totf=0,cur; 
		int totc = 0;
		while(1) 
		{  
			getPath(src,sink);
			if (flow[sink]==0)
				break;
			if (path[sink]==-1)
				break;
			for (int cur = sink ; cur!= src; cur = E[path[cur]].fr) {
				E[path[cur]].flow -= flow[sink];
				int ind = path[cur]%2 ? path[cur]-1 : path[cur]+1;
				E[ind].flow += flow[sink];
				totc+= flow[sink]*E[path[cur]].cost;
			}
			totf += flow[sink];
		} 
		return make_pair(totf,totc); 
	} 
	void clear() 
	{ 
		E.clear(); 
		memset(flow,0,sizeof(flow)); 
		memset(cost,0,sizeof(cost)); 
		memset(path,-1,sizeof(path)); 
	} 
}; 

int AA[209];
int BB[209];
double C[209][209];
int main()
{
	freopen("input.in","r" , stdin);

	int A,B;
	int kase=0;
	while(scanf("%d %d" , &A , &B) ==2)
	{
		if(!A && !B)break;
		n = A+B+2;
		int factor = 10000;
		MinCostMaxFlow M = MinCostMaxFlow();
		int src = 0 , sink = A+B+1;

		FOR(i,0,A)
		{
			scanf("%d",&AA[i]);
			M.AddEdge(src , i+1 , 0 , AA[i]);
		}
		FOR(i,0,B)
		{
			scanf("%d",&BB[i]);
			M.AddEdge( A+i+1 , sink , 0 , BB[i]);
		}
		FOR(i,0,A)
			FOR(j,0,B)
		{
			cin>>C[i][j];
			C[i][j]*=factor;
			if((int)C[i][j]!=-1*factor)	
				M.AddEdge(i+1 , A+j+1 , C[i][j] , oo);
			
		}
		
		
		///////////

		MinCostMaxFlow M2 = MinCostMaxFlow();

		FOR(i,0,A)
			M2.AddEdge(src , i+1 , 0 , AA[i]);

		FOR(i,0,B)	
			M2.AddEdge( A+i+1 , sink , 0 , BB[i]);

		FOR(i,0,A)
			FOR(j,0,B)
			if((int)C[i][j]!=-1*factor)
				M2.AddEdge(i+1 , A+j+1 , -C[i][j] , AA[i]);


		double res = M.MCMF(src,sink).second;
		double res2 = M2.MCMF(src,sink).second;
		printf("Problem %d: %.2f to %.2f\n", ++kase, fabs((double)res/(double)factor), fabs((double)res2/(double)factor));

	}
	return 0;
}