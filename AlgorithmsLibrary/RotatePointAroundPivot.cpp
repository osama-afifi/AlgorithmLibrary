#include<iostream>
#include<iomanip>
#include<string>
#include<cstring>
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<map>
#include<sstream>
#include<queue>
#include<set>
#include<stack>
#include<math.h>

#define FOR(i, a, b) for( int i = (a); i < (b); i++ )
#define ALL(A) A.begin(), A.end()
#define Set(a, s) memset(a, s, sizeof (a))
#define pb push_back
#define mp make_pair
typedef long long LL;

using namespace std;

struct  point
{
	LL x,y;
};


point rotateP(point q , point r, int count)
{

	LL M[4][4] = { {0,-1},
					{1,0},
	};
	LL V[4] = {q.x-r.x,q.y-r.y};
	LL res[4]={0};
	while(count--)
	{
		res[0]=0;
		res[1]=0;
		res[2]=0;

		FOR(i,0,2)
			FOR(j,0,2)
			res[i]+=V[j]*M[i][j];

		V[0]=res[0];
		V[1]=res[1];
	//	V[2]=1;

	}

	point ret = {res[0]+r.x , res[1]+r.y};
	return ret;
}