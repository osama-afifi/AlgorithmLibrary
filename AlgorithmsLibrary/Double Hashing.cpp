// Double Hashing

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


void pre(int len,LL p[], LL inv[], LL B=31, LL M=1e9+7)
{
	p[0] = 1;
	for(int i =1 ; i<=len ; i++ )
	{
		p[i] = (p[i-1]*B)%M;
		inv[i] = modInv(p[i], M);	
	}
}


void H(string &s, LL arr[], LL p[], LL M=1e9+7)
{
	arr[0] = s[0];
	for(int i =1 ; i<s.length() ; i++ )
		arr[i] = (arr[i-1] + (LL)(s[i])*p[i]) %M;
	
}

LL getHash(int a  , int b , LL arr[],LL inv[], LL M=1e9+7)
{
	if(a==0)return arr[b];
	LL x = arr[b]-arr[a-1];
	if(x<0)x+=M;
	LL ret =  (x*inv[a])%M;
	return ret;
}

LL hp1_1[5009];
LL hp2_1[5009];
LL hp1_2[5009];
LL hp2_2[5009];

LL hp1[5009];
LL hp2[5009];

LL hs1[5009];
LL hs2[5009];


LL M1  = 1000LL*1000LL*1000LL+7LL;
LL B1  = 31;
LL M2  = (1LL<<31)-1LL;
LL B2  = 10007;

LL pw1[5009];
LL inv1[5009];

LL pw2[5009];
LL inv2[5009];


int main()
{
	freopen("input.in", "r" , stdin);

	pre(5000,pw1,inv1,B1,M1);
	pre(5000,pw2,inv2,B2,M2);
	string s,p1,p2;

	while(cin>>s)
	{
		
		int n  = s.length();
		cin>>p1;
		cin>>p2;

		H(s,hs1,pw1,M1);
		H(s,hs2,pw2,M2);

		H(p1,hp1_1,pw1,M1);
		H(p1,hp1_2,pw2,M2);
		H(p2,hp2_1,pw1,M1);
		H(p2,hp2_2,pw2,M2);

		int l1 = p1.length();
		int l2 = p2.length();
		int count =0;
		unordered_set< LL > S;
		for(int i=0;i+l1<=n ; i++)
		{
			if((getHash(i,i+l1-1,hs1,inv1,M1)== hp1_1[l1-1]) && (getHash(i,i+l1-1,hs2,inv2,M2)== hp1_2[l1-1]))
				for(int j = i;j+l2<=n ; j++)
					if( (j+l2>=i+l1 && (getHash(j,j+l2-1,hs1,inv1,M1) ==  hp2_1[l2-1] ) && (getHash(j,j+l2-1,hs2,inv2,M2) ==  hp2_2[l2-1] )))
						S.insert( getHash(i,j+l2-1,hs1,inv1,M1) * M2 +  getHash(i,j+l2-1,hs2,inv2,M2));		
				
		}

			printf("%d\n" , S.size());
	}
	return 0;
}