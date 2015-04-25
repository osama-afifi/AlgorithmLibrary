#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i = (a) ; i<b ; i++)
#define Set(a,b) memset(a,b,sizeof(a))
#define mp make_pair
#define pb push_back
#define all(v) (v.begin(), v.end())
typedef long long LL;
using namespace std;
LL MOD = 1e9+7;

char arr[100009];
int n;
int c=0;
int tot=0;
vector< vector<int> >V;
string res="";
bool solve(int &idx)
{
    if(!arr[idx])
        return false;
    bool ok=0;
    if(arr[idx]=='i')
    {
        res.push_back('i');
        res.push_back('n');
        res.push_back('t');
        ++c;
        return true;
    }
    else if(arr[idx]=='p')
    {
        res.push_back('p');
        res.push_back('a');
        res.push_back('i');
        res.push_back('r');
        res.push_back('<');
        ++idx;
        if(!solve(idx))return false;
       res.push_back(',');
       ++idx;
        if(!solve(idx))return false;
        res.push_back('>');
        return true;
    }
    return false;
}

int main()
{
    cin>>n;

        c=0;
        string s;
        tot=0;
        while(cin>>s)
        {
            arr[tot++]=s[0];
        }

        res="";
        int idx=0;
        bool b = solve(idx);
        if(!b || c!=n || tot!=idx+1)
        {
            puts("Error occurred");
        }
        else
            cout << res << "\n";


    return 0;
}
