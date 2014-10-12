#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <stack>

#define FOR(i, a, b) for( int i = (a); i < (b); i++ )
#define Fore(it, x) for(typeof (x.begin()) it = x.begin(); it != x.end (); it++)
#define Set(a, s) memset(a, s, sizeof (a))
#define mp make_pair
using namespace std;

const int MX = 709; 
bool Findath(vector<vector<int> > &canMatch,vector<int> &left,vector<int> &right,vector<bool>& visited,int i)
{

	FOR(j,0,canMatch[i].size())
	{
		int z = canMatch[i][j];
		if(visited[z])
			continue;
		visited[z]=1;
		if(right[z]==-1 || Findath(canMatch,left,right,visited,right[z]))
		{
			left[i]=z;
			right[z]=i;
			return true;
		}
	}
return false;
}

int maxMatch(vector<vector<int> > &canMatch,int matchingtoSize,vector<int> &left,vector<int> &right)
{
	left.clear();
	right.clear();
	left.resize(canMatch.size(),-1);
	right.resize(matchingtoSize,-1);
	int sol=0;
	FOR(i,0,canMatch.size())
	{
		vector<bool> visited(matchingtoSize);
		if(left[i]==-1)
		{
			if(Findath(canMatch,left,right,visited,i))
				sol++;
		}
	}
	return sol;
}

int maxMatch(vector<vector<int> > &canMatch,int matchingtoSize)
{
	vector<int> left,right;
	return maxMatch(canMatch,matchingtoSize,left,right);
}

char arr[MX][MX];
int col[MX][MX];
int row[MX][MX];
int main()
{
	freopen("input.in","r" , stdin);
	int t;
	scanf("%d",&t);
	while(t--)
	{
		int n,m;
		scanf("%d%d",&n,&m);

		FOR(i,0,n)
			FOR(j,0,m)
			scanf(" %c",&arr[i][j]);		
		int k1 = 0;
		FOR(i,0,n)
			FOR(j,0,m)
		{
			if(arr[i][j]=='H' || arr[i][j]=='D')
			{
				while(j<m &&(arr[i][j]=='H' || arr[i][j]=='D'))
				{
					col[i][j] = k1;
					j++;
				}
				k1++;
			}
		}

		int k2=0;
		FOR(j,0,m)
			FOR(i,0,n)	
		{
			if(arr[i][j]=='H' || arr[i][j]=='D')
			{
				while(i<n &&(arr[i][j]=='H' || arr[i][j]=='D'))
				{
					row[i][j] = k2;
					i++;
				}
				k2++;
			}
		}

		vector<vector<int> > G(k1);

		FOR(i,0,n)
			FOR(j,0,m)
			if(arr[i][j]=='H')
				G[col[i][j]].push_back(row[i][j]);

		int res = maxMatch(G, k2);
		printf("%d\n",res);
	}
	return 0;
}

