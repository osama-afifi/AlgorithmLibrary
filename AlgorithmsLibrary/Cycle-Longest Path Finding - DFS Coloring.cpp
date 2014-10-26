#include <bits/stdc++.h>

#define FOR(i, a, b) for( int i = (a); i < (b); i++ )
#define ALL(A) A.begin(), A.end()
#define Set(a, s) memset(a, s, sizeof (a))
#define pb push_back
#define mp make_pair
typedef long long LL;

using namespace std;


int G[30][30];
int vis[30];
int cycle;
int from[30];
int d[30];


void dfs(int cur, int p)
{
    if(cycle!=-1)return;
    if(vis[cur]==2)return;
    from[cur]=p;
    if(vis[cur]==1)
    {
        cycle=cur;
        return;
    }
    vis[cur]=1;
    FOR(i,0,26)
        if(G[cur][i])
        {
            dfs(i,cur);
            d[cur]=max(d[cur],d[i]+1);
        }

    vis[cur]=2;
}

int main()
{
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r" , stdin);

    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        Set(d,0);
        FOR(i,0,26)FOR(j,0,26)G[i][j]=1;
        FOR(i,0,n)
            {
                string s;
                cin>>s;
                G[s[0]-'a'][s[1]-'a']=0;
            }
        cycle=-1;
        Set(vis,0);
        Set(from,-1);
        FOR(i,0,26)
                dfs(i,-1);
        vector<int>P;
        if(cycle!=-1)
        {
            int c=39;
            while(c--)
            {
            P.pb(cycle);
            cycle = from[cycle];
            }
            reverse(P.begin(),P.end());
        }
        else
        {
            int start=0;
            FOR(i,0,26)
                if(d[i]>d[start])
                    start=i;
             P.push_back(start);
            while(d[start]>0)
            {

                FOR(i,0,26)
                    if(G[start][i] && d[start]==d[i]+1)
                    {
                    start=i;
                    P.push_back(start);
                    break;
                    }
            }

        }


        int dim = (P.size()+1)/2;
        FOR(i,0,dim)
        {
            FOR(j,0,dim)
                cout << (char)(P[i+j]+'a');
            cout << endl;
        }

    }
    return 0;
}

