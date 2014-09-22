#include<iostream>
#include<string>
#include<stdio.h>
#include<cstring>
#include<vector>
#include<set>

using namespace std;
int G[55][55];
bool used[55];
bool vis[55][55];
bool floyd[55][55];
int deg[55];

int maxi;
const int oo =1<<25;
vector<int>sol;
int s=0;
void euler(int node)
{

	for(int i =1;i<=50;i++)
		if(used[i])
			if(G[node][i]>0)
			{
				G[node][i]--;G[i][node]--;
				euler(i);
				s^=1;
		//		if(s)
		//			printf("%d %d\n",node,i);
		//		else
					printf("%d %d\n",i,node);
			}
}

int main()
{
	freopen("input.in","r",stdin);
	int t,e,kase=0,n1,n2;
	scanf("%d",&t);
	while(t--)
	{
		s=1;
		sol.clear();
		maxi=0;
		memset(deg,0,sizeof deg);
		memset(used,0,sizeof used);
		memset(G,0,sizeof G);
		memset(vis,0,sizeof vis);

		scanf("%d",&e);

		for(int i =0 ; i< e ; i++)
		{
			scanf("%d%d",&n1,&n2);
			G[n1][n2]++;
			G[n2][n1]++;
			floyd[n1][n2]=floyd[n2][n1]=1;
			deg[n1]++;
			deg[n2]++;
			used[n1]=used[n2]=1;
		}

		bool valid=1;
		int count=0;
		for(int i =1 ; i<= 50 ; i++)
			if(deg[i]&1)
				valid=0;

		printf("Case #%d\n",++kase);

		int i,j,k;
		for( k =1 ; k<= 50 ; k++)
			if(used[k])
				for( i =1,floyd[k][k]=1 ;  i<= 50 ; i++)
					if(used[i])
						for( j =1 ; j<= 50 ; j++)
							if(used[j])
								floyd[i][j] |= floyd[k][j];

		for( i =1 ; i<= 50 ;i++)
			for( j =1 ; j<= 50 ; j++)
				if(used[i] && used[j] && !floyd[i][j] )
					valid=0;

		if(valid)
		{
			s=0;
			int mini=oo;
			int indi;
			for(int i = 1 ; i <=50 ; i++)
				if(used[i])
					if(deg[i]>0 && deg[i]<mini)
					{
						indi=i;
						mini=deg[i];
					}
					if(mini==oo)
						puts("some beads may be lost");
					else
						euler(indi);

		}
		else
			puts("some beads may be lost");

		if(t)putchar('\n');
	} 

	return 0;
}