#include <iostream>
#include <stdio.h>

using namespace std;

struct Edge
{int n1,n2,cost;};

int const oo =1<<25;

Edge links[2500];
int path[2500];
int n,m;

bool Bellman(int s)
{
	for(int i = 0 ; i<n ; i++)
		path[i]=oo;

	path[s]=0;

	for(int i = 0 ; i<n-1 ; i++)
		for(int j = 0 ; j<m ; j++)
		{
			if(path[links[j].n1]+links[j].cost<path[links[j].n2])
				path[links[j].n2]=path[links[j].n1]+links[j].cost;
		}
		for(int j = 0 ; j<m ; j++)
			if(path[links[j].n1]+links[j].cost<path[links[j].n2])
				return true;
		return false;
}

int main()
{
	freopen("input.in","r",stdin);
	int t;
	scanf("%d",&t);
	int n1,n2,cost;
	while(t--)
	{
		scanf("%d%d",&n,&m);

		for(int i = 0 ; i<m ; i++)
		{
			scanf("%d%d%d",&n1,&n2,&cost);
			links[i].n1=n1;
			links[i].n2=n2;
			links[i].cost=cost;
		}

		     if(Bellman(0))
            printf("possible\n");
			 else
            printf("not possible\n");

	}


	return 0;
}