#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

int const oo = 1<<25;

struct Node
{
	int node,cost;

	bool operator <(const Node &a) const
	{

		return cost>a.cost;

	}
};

int LINK[201][201];
int path[201][201];
int taxes[201];

void PrintPath(int s , int t)
{
	if(path[s][t]==-1)return;
	PrintPath(s,path[s][t]);
	printf("-->%d" ,path[s][t] + 1);
	PrintPath(path[s][t],t);
}

int main()
{
	freopen("input.in","r",stdin);

	int test,kase=0;

	scanf("%d",&test);
	cin.ignore(2);

	int m,n,s,t;
	int n1,n2,cost;
	while(test--)
	{
		//	memset(LINK,-1,sizeof(LINK));	
		//memset(path,-1,sizeof(path));
		string text;
		getline(cin,text);
		stringstream ss;
		ss<<text;

		n=0;
		while(ss>>LINK[0][n])
		{	
			path[0][n]=-1;
			if(LINK[0][n]==-1)
				LINK[0][n]=oo;
			n++;
		}


		for(int i = 1 ; i < n ; i++)
			for(int j = 0 ; j < n ; j++)
			{
				path[i][j]=-1;
				cin>>LINK[i][j];
				if(LINK[i][j]==-1)
					LINK[i][j]=oo;
			}

			for(int i = 0 ; i < n ; i++)
				cin>>taxes[i];

			
			cin.ignore();

			///////////////////////////////////
			/*Floyd Warshal*/

			for (int k = 0; k < n; k++ )
				for (int i = 0; i < n; i++ )
					for (int j = 0; j < n; j++ )
					{
						if(LINK[i][j] > LINK[i][k] + LINK[k][j] + taxes[k] )
						{
							LINK[i][j] =  LINK[i][k] + LINK[k][j] + taxes[k];
							path[i][j] = k;
						}
					}
			////////////////////////////////////

					bool first=true;
					while(getline(cin,text))
					{
						if(text=="")break;
						if(!first)printf("\n");
						first=false;
						
						stringstream sss;
						sss<<text;
						sss>>s>>t;
					
						printf("From %d to %d :\n",s,t);
						if(s==t)
						{
						printf("Path: %d\n",s);
						}
						else
						{
						printf("Path: %d",s);
						PrintPath(s-1, t-1);
						printf("-->%d\n",t);
						}
						printf("Total cost : %d\n",LINK[s-1][t-1]);

					}
					if(test)printf("\n");
	}


	return 0;
}


