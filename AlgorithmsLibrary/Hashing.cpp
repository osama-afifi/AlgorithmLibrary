#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

typedef long long LL;

using namespace std;

LL M  = 1e9+7;
LL B  = 29;
LL p[50009];
LL inv[50009];


LL powerMod(LL n, LL p, LL m) { 
  if (p==0) 
    return 1; 
  LL x = powerMod(n, p/2, m); 
  x = (x * x) % m; 
  if (p & 1LL) 
    x = (x * n) % m; 
  return x; 
} 
 
LL modInv(int x, int m) { 
  return powerMod(x, m - 2, m); 
}


void pre(int len)
{
	p[0] = 1;
	for(int i =1 ; i<=len ; i++ )
	{
		p[i] = (p[i-1]*B)%M;
		inv[i] = modInv(p[i], M);	
	}
}


void H(string &s, LL arr[])
{
	arr[0] = s[0];
	for(int i =1 ; i<s.length() ; i++ )
		arr[i] = (arr[i-1] + (s[i])*p[i]) %M;
	
}

LL getHash(int a  , int b , LL arr[])
{
	if(a==0)return arr[b];
	LL x = arr[b]-arr[a-1];
	if(x<0)x+=M;
	LL ret =  (x*inv[a])%M;
	return ret;
}

LL hsh[50009];

int main(){
	freopen("input.in", "r", stdin);
	int t;
	int kase = 0;
	pre(50001);

	scanf("%d" , &t);
	while(t--)
	{
		string s;
		cin>>s;
		H(s,hsh);
		int len =s.length();
		int res = 0;
		int st = 0;
		int i = 0;
		for(int i = 0 ; i<len/2 ; i++)
		{
			LL h1 = getHash(st,i,hsh);
			LL h2 = getHash(len-1-i, len-1-st, hsh);
			if(h1 == h2)
				st = i+1 , res+=2;
		}

		printf("Case #%d: %d\n" , ++kase , res + (len&1 || st<len/2));

	}
	return 0;
}

