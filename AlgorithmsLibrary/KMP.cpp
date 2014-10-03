#include<iostream>
#include<iomanip>
#include<string>
#include<cstring>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<set>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#define FOR(i, a, b) for( int i = (a); i < (b); i++ )
#define ALL(A) (A.begin(), A.end())
#define Set(a, s) memset(a, s, sizeof (a))
#define pb push_back
#define mp make_pair
typedef long long LL;
using namespace std;


void failureFunction(string &p, int F[])
{
	int m = p.size(), k = 0;
	F[0] = 0;
	for (int q = 1; q < m ; ++q) 
	{
		while (k > 0 && p[k] != p[q])
			k = F[k - 1];
		if (p[k] == p[q])
			k++;
		F[q] = k;
	}
}

vector<int> KMP(string &p, string&s, int F[])
{
	vector<int>M;
	failureFunction(p,F);
	int q=0;
	for(int i = 0 ; i<s.length() ; i++)
	{
		while(q && s[i]!=p[q]) q = F[q-1];
		if(s[i]==p[q])	q++;
		if(q==p.length())
		{
			M.push_back(i-p.length()+1);
			q = F[q-1];
		}
	}
	return M;
}

int main()
{
	freopen("input.in", "r" , stdin);
	int F[100];
	string s = "OsamaisaabigOsamaforrealOsama";
	string p = "Osama";
	vector<int>M=KMP(p,s,F);
	FOR(i,0,M.size())
		cout << M[i] << " ";
	cout <<endl;


	return 0;
}