#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;


struct point 
{
	int x,y;
	point(int x, int y) : x(x), y(y)
	{}
};

char arr[6][6];

struct rectangle
{
	point ul,br;
	rectangle(point ul, point br) : ul(ul), br(br)
	{}
	int area()
	{
		return ((br.x-ul.x)*(br.y-ul.y));
	}
	bool safe()
	{
		bool a = 0 , m = 0;
		for(int i=ul.y;i<br.y; i++)
			for(int j=ul.x;j<br.x; j++)
			{
				a |= arr[i][j]=='A';
				m |=arr[i][j]=='M';
			}
		return !(a && m);
	}
};

int n,m;


int solve(rectangle r)
{
	if(r.area()<=0)
		return 0;
	if(r.safe())
		return 0;
	int mini = 1<<25;
	// vertical lines
	for(int i=r.ul.x+1 ; i<r.br.x ; i++)
		mini = min(mini , solve(rectangle(r.ul,point(i,r.br.y))) + solve(rectangle(point(i,r.ul.y),r.br)) +1 );	
	// horizontal lines
	for(int i=r.ul.y+1 ; i<r.br.y ; i++)
		mini = min(mini , solve(rectangle(r.ul,point(r.br.x,i))) + solve(rectangle(point(r.ul.x,i),r.br)) +1 );	
	return mini;
}

int main() 
{
	freopen("input.in", "r", stdin);
	int t;
	cin >> t;
	int kase=0;
	while(t--)
	{
		cin>>n>>m;
		for(int i = 0 ; i<n ; i++)
			for(int j = 0 ; j<m ; j++)
				cin>>arr[i][j];

		int res = solve(rectangle(point(0,0), point(m,n)));
		cout << "Case #" << ++kase << ": " << res << endl;
	}
	return 0;
}