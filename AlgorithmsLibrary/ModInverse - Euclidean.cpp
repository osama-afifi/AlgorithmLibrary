#include <bits/stdc++.h>

#define FOR(i, a, b) for( int i = (a); i < (b); i++ )
#define ALL(A) A.begin(), A.end()
#define Set(a, s) memset(a, s, sizeof (a))
#define pb push_back
#define mp make_pair
typedef long long LL;

using namespace std;

__inline LL square(long long x)
{
	return x*x;
}
long long bigmod(long long  b,long long  p, long long  m)
{
	if(p==0)
		return 1;
	else if(p%2==0)
		return square((bigmod(b,p/2,m)))%m;
	else
	return ((b%m)*(bigmod(b,p-1,m))%m)%m;

}
long long  modInverse(long long  a, long long  n) {
	return bigmod(a,n-2, n)%n;
}

LL mod_inv( LL a, LL m )
{
  if( m == 1 )
    return 1;
  LL x = 0, y = 1;
  LL r = m, s = a % m;
  while( s )
  {
    LL q = r / s;
    LL t = y;
    y = x - q * y, x = t;
    t = s;
    s = r - q * s, r = t;
  }
  if( r > 1 )
    return -1;
  if( x < 0 )
    x += m;
  return x;
}

LL euler(LL n)
{
        LL x=n;
		LL res = x;
		for(LL j=2;j*j<=x;j++)
		{
		if(x%j==0)
				res -= res/j;
			while(x%j==0)
			x/=j;
		}
		if(x>1)
			res -= res/x;
    return res;
}

int main()
{
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r" , stdin);

    LL n,e,c;
    while(cin>>n>>e>>c)
    {
        LL d = mod_inv(e,euler(n));
        LL m = bigmod(c,d,n);
        cout << m << endl;
    }

    return 0;
}

