
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <map>
#include <set>
#include <queue>
#include <time.h>
#include <limits.h>

using namespace std;
#define FOR(i, a, b) for( int i = (a); i < (b); i++ )
#define Fore(it, x) for(typeof (x.begin()) it = x.begin(); it != x.end (); it++)
#define Set(a, s) memset(a, s, sizeof (a))
#define mp make_pair 
#define MAX 10009 
using namespace std;
const int MAXN = 100100;
#define INF (1<<30)
struct treap{
	
	struct node 
	{
		node *Left, *Right;
		int key, pri, sz, best;
	} *root, *dummy;
 
	treap() 
	{
		dummy = new node();
		dummy->Left = dummy->Right = dummy;
		dummy->pri = -1;
		dummy->sz = 0;
		dummy->best=-INF;
		root = dummy;
		srand(23524677);
	}
	
	int size() { return root->sz; }
 
	void update(node *n) 
	{ 
		n->best=max(n->key,max(n->Left->best,n->Right->best));
		n->sz = n->Left->sz + n->Right->sz + 1; 
	}
	
	
	node *rotate(node *A, node *B) 
	{
		if (A->Left == B) {
		  A->Left = B->Right;
		  B->Right = A;
		} else {
		  A->Right = B->Left;
		  B->Left = A;
		}
		update(A);
		update(B);
		return B;
	}
	
	node *insert(node *root, node *newnode,int pos) 
	{
			if (root == dummy) 	return newnode;
						
			if (root->Left->sz>=pos) 
			{
				root->Left = insert(root->Left, newnode,pos);
				if (root->Left->pri > root->pri) root = rotate(root, root->Left);
			}
			else 
			{
				root->Right = insert(root->Right, newnode,pos-root->Left->sz-1);
				if (root->Right->pri > root->pri) root = rotate(root, root->Right);
			}
			update(root);
			return root;
	}
	
	void insert(int key,int pos) 
	{
		node *n = new node();
		n->Left = n->Right = dummy;
		n->key = key;
		n->pri = rand();
		n->best=key;
		n->sz = 1;
		root = insert(root, n,pos);
	}
	
	int query( int lo, int hi, int a, int b, node *x ) 
	{		
		 if( a > hi || b < lo || x == dummy ) return -INF;
		 
		 if(a>=lo && b<=hi) return x->best;
		  int ret = -INF;
		 ret = max( ret, query( lo, hi, a, a + x->Left->sz, x->Left ) );
         ret = max( ret, query( lo, hi, a + x->Left->sz + 1, b, x->Right ) );
         int cno=a+x->Left->sz;
         
         
         if(cno>=lo && cno<=hi)  
		 {	 
			 ret=max(ret,x->key);
		 }
		 else 
			 return ret;
         return ret;
	}
	int query(int lo,int hi)
	{
		return query(lo,hi,1,root->sz,root);
	}
	
	
};

int main() 
{
	freopen("input.in","r",stdin);
	int q;
	scanf("%d ", &q);
	treap T;
			srand(time(NULL));
	while (q--) 
	{

		char c;
		int x,y;
		scanf(" %c%d%d", &c, &x, &y);
//		printf("%c %d %d\n", c, x, y);
		if (c == 'A') 
			T.insert(x,y-1);	
		else if (c == 'Q') 
			printf("%d\n", T.query(x,y));
		

	}
	
	return 0;
}
