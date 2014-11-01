#include <bits/stdc++.h>

#define FOR(i, a, b) for( int i = (a); i < (b); i++ )
#define ALL(A) A.begin(), A.end()
#define Set(a, s) memset(a, s, sizeof (a))
#define pb push_back
#define mp make_pair
typedef long long LL;

using namespace std;



int main()
{
    ios_base::sync_with_stdio(0);
    freopen("input.txt", "r" , stdin);

    string s;
    while(cin>>s)
    {
        priority_queue<int>Q1;
        priority_queue<int>Q2;
        if(s!="#")
        {
            int num;
            stringstream ss;
            ss<<s;
            ss>>num;
            if((int)Q2.size()>(int)Q1.size())
                Q1.push(num);
            else
                Q2.push(-num);
        }
        else
        {
            int res;
            if(Q2.size()>Q1.size())
            {
                res = - Q2.top();
                Q2.pop();
            }
            else
            {
                res = Q1.top();
                Q1.pop();
            }
            cout << res <<endl;
        }
    }


    return 0;
}

