#include <bits/stdc++.h>

#define FOR(i, a, b) for( int i = (a); i < (b); i++ )
#define ALL(A) A.begin(), A.end()
#define Set(a, s) memset(a, s, sizeof (a))
#define pb push_back
#define mp make_pair
typedef long long LL;

using namespace std;
const int N = 1000005;
LL T[N<<2];
LL L[N<<2];

void refresh(int x)
{
    T[x] |= L[x];
    L[2*x] |= L[x];
    L[2*x+1] |= L[x];
    L[x]=0;
}

void update(int l , int r , int x , int a , int b , LL v)
{
    refresh(x);
    if(l>b || r<a || l>r) return;
    if(l>=a && r<=b)
    {
      //  T[x] |= v;
        L[x] |= v;
        //refresh(x);
        return ;
    }

    int mid=(l+r)/2;
    update(l,mid,x*2,a,b,v);
    update(mid+1,r,x*2+1,a,b,v);
    T[x] = T[x*2]&T[x*2+1];
}

LL query(int l , int r , int x,  int a , int b)
{
    refresh(x);
    if(l>b || r<a || l>r) return (1LL<<50)-1;;
    if(l>=a && r<=b)
        return T[x];

    int mid=(l+r)/2;
    LL q1 = query(l,mid,x*2, a,b);
    LL q2 = query(mid+1,r,x*2+1,a,b);
    return q1 & q2;
}

LL Q[100009][3];
int main()
{
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r" , stdin);

    int n,m;
    while(cin>>n>>m)
    {
     Set(T,0);
     Set(L,0);


    FOR(i,0,m)
        FOR(j,0,3)cin>>Q[i][j];

    FOR(i,0,m)
        update(0,n-1,1,Q[i][0]-1,Q[i][1]-1,Q[i][2]);

    bool ok=1;
    FOR(i,0,m)
            ok &= query(0,n-1,1,Q[i][0]-1,Q[i][1]-1)==Q[i][2];

        if(!ok)
            cout << "NO" <<endl;

        else
            {
            cout << "YES" <<endl;
    FOR(i,0,n)
        cout << query(0,n-1,1,i,i) << " ";
    cout << endl;
    }
    }
    return 0;
}

