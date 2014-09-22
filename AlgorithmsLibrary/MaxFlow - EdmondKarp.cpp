#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <queue>
#include <map>
#include <set>

using namespace std;

int const oo=1<<20;
int flow[1001][1001];

int vis[1001];
int mini=oo;
int indexx;

bool BFS(int s , int t)
{
	queue <int> BFS;
	for(int i = 0 ; i<=indexx ; i++)
		vis[i]=-1;
	BFS.push(s);
	int current;
	while(!BFS.empty())
	{
		current=BFS.front();
		if(current==t)
			return true;
		BFS.pop();
		for(int i = 0 ; i< indexx ; i++ )
		{
			if(vis[i]==-1 && flow[current][i]/*>0*/ )
			{
				vis[i]=current;
				BFS.push(i);
			}
		}
	}
	return false;
}

void get_flow(int s,int node)
{
	if(s==node)
		return;
	if(flow[vis[node]][node]<mini)
		mini=flow[vis[node]][node];

	get_flow(s,vis[node]);
	flow[vis[node]][node]-=mini;	
	flow[node][vis[node]]+=mini;

}

int edmond_carp(int s , int t)
{
	int maxflow=0;
	while(BFS(s,t))
	{
		get_flow(s,t);
		maxflow+=mini;
		mini=oo;
	}
	return maxflow;
}

int main()
{
	freopen("input.in","r",stdin);
	int t,n,m,k;
	string text,text2;
	scanf("%d",&t);
	while(t--)
	{
		memset(flow,0,sizeof flow);
		map<string,int> M;

		scanf("%d",&n);
		indexx=2;
		for(int i = 0 ; i < n ; i++)
		{
			cin>>text;
			if(M.find(text)==M.end())
				M[text]=indexx++;
			flow[0][M[text]]++;
		}
		scanf("%d",&m);

		for(int i = 0 ; i < m ; i++)
		{
			cin>>text;
			cin>>text;
			if(M.find(text)==M.end())
				M[text]=indexx++;
			flow[M[text]][1]++;
		
		}

		scanf("%d",&k);
		for(int i = 0 ; i < k ; i++)
		{
			cin>>text>>text2;
			if(M.find(text)==M.end())
				M[text]=indexx++;
			if(M.find(text2)==M.end())
				M[text2]=indexx++;
			flow[M[text2]][M[text]]=oo;
		}
				printf("%d\n",m-edmond_carp(0,1));
				if(t)putchar('\n');
	}

	return 0;
}

