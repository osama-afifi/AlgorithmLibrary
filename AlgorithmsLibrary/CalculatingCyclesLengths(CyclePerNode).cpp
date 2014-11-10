#include <bits/stdc++.h>

#define FOR(i, a, b) for( int i = (a); i < (b); i++ )
#define ALL(A) A.begin(), A.end()
#define Set(a, s) memset(a, s, sizeof (a))
#define pb push_back
#define mp make_pair
typedef long long LL;

using namespace std;

int cycle[10009];
int cycleCost[10009];
bool vis[10009];
int dist[10009];
vector< vector<pair<int,int> > >G;
int c=0;
int cycleStart;
int dfs(int cur,int prev)
{
    vis[cur]=1;
    FOR(i,0,G[cur].size())
    {
        int v=G[cur][i].first;
        if(v==cycleStart && v!=prev)
        {
            //cycle[v]=cycle[cur]=c;
            return G[cur][i].second; // indicate cycle detection
        }

        if(v==prev)continue;
        if(!vis[v])
        {
            int found = dfs(v, cur);
            if(found)
            {
                cycle[cur]=cycle[v]=c;
                return found+G[cur][i].second;
            }
        }
    }
    return 0;
}

int n,m;

void dijkstra(int st)
{
    FOR(i,0,n)
    dist[i] = (int)1e9;
    priority_queue<pair<int,int>, vector<pair<int,int> > , greater<pair<int,int> > >Q;
    Q.push(mp(0,st));
    dist[st]=0;
    while(Q.size())
    {
        pair<int,int>temp = Q.top();
        Q.pop();
        int cost = temp.first;
        int cur = temp.second;
        if(cost>dist[cur])continue;
        FOR(i,0,G[cur].size())
            {
                int v = G[cur][i].first;
                int newCost = dist[cur]+G[cur][i].second;
                if(dist[v]>newCost)
                   {
                       dist[v]=newCost;
                    Q.push(mp(newCost,v));
                   }

            }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r" , stdin);

    while(scanf("%d %d", &n, &m)==2)
    {
        G.clear();
        G.resize(n);
        FOR(i,0,m)
        {
            int a,b,c;
            scanf("%d %d %d", &a, &b, &c);
            --a,--b;
            G[a].pb(mp(b,c));
            G[b].pb(mp(a,c));
        }
        Set(cycle,-1);
        Set(cycleCost,0);
        c=0;
        FOR(i,0,n)
        {
            if(G[i].size()>1 && cycle[i]==-1)
            {
                Set(vis,0);
                cycleStart = i;
                int found = dfs(i,-1);
                if(found)
                    cycleCost[c] = found,c++;
            }
        }

        int q;scanf("%d",&q);

        while(q--)
        {
            int st,fat;
            int mini=(int)1e9;
            scanf("%d %d", &st, &fat);
            st--;
            dijkstra(st);
        FOR(i,0,n)
            {
                  if(cycle[i]!=-1 && cycleCost[cycle[i]]>=fat)
                    {
                    int cost = 2*dist[i] + cycleCost[cycle[i]];
                        mini = min(mini,cost);
                    }
            }


            if(mini>=(int)1e9)
                cout << -1 <<endl;
            else
            cout << mini <<endl;
        }
    }

    return 0;
}

