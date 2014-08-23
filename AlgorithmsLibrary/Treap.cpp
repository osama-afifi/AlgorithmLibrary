#include <stdio.h>
#include <limits>

using namespace std;

typedef int nt;

struct Node;
extern Node *empty;
// This treaps support multiset values
// check for existence first if you want unique elements
struct Node 
{
	nt val;
	int priority;
	int s; // size
	int frq;
	Node *lf, *rt;
	Node() : priority(INT_MIN), s(0), frq(0), lf(empty), rt(empty) 
	{}
	Node(const nt &val, int pri) :		val(val), priority(pri), s(1), frq(1), lf(empty), rt(empty) 
	{}
	void updateSize() 
	{
		s = lf->s + rt->s + frq;
	}
	const nt &operator [](int idx) 
	{
		if (idx < lf->s) return (*lf)[idx];
		idx -= lf->s + frq;
		if (idx >= 0) return (*rt)[idx];
		return val;
	}
	int size() const 
	{
		return s;
	}
};

Node *empty = new Node();

inline int lower_bound(Node *root, const nt &v) 
{
	int ret = 0;
	while (root != empty) 
	{
		if (v < root->val) 
			root = root->lf;
		else if (root->val < v)
		{
			ret += root->lf->s + root->frq;
			root = root->rt;
		}
		else 
		{
			ret += root->lf->s;
			break;
		}
	}
	return ret;
}

inline int upper_bound(Node *root, const nt &v) 
{
	int ret = 0;
	while (root != empty) 
	{
		if (v < root->val)
			root = root->lf;
		else if (root->val < v)
		{
			ret += root->lf->s + root->frq;
			root = root->rt;
		}
		else 
		{
			ret += root->lf->s + root->frq;
			break;
		}
	}
	return ret;
}

inline Node *rotate_left(Node *P) 
{
	Node *Q = P->rt;
	P->rt = Q->lf;
	Q->lf = P;
	P->updateSize();
	Q->updateSize();
	return Q;
}

inline Node *rotate_right(Node *Q) 
{
	Node *P = Q->lf;
	Q->lf = P->rt;
	P->rt = Q;
	Q->updateSize();
	P->updateSize();
	return P;
}

inline Node *balance(Node *root) 
{
	if (root->lf->priority > root->priority) root = rotate_right(root);
	if (root->rt->priority > root->priority) root = rotate_left(root);
	return root;
}

inline Node *insert(Node *root, const nt &val, int pri = rand()) 
{
	if (root == empty) return new Node(val, pri);
	if (val < root->val) root->lf = insert(root->lf, val, pri);
	else if (root->val < val) root->rt = insert(root->rt, val, pri);
	else root->frq++;
	root->updateSize();
	return balance(root);
}

inline Node *erase(Node *root, const nt &val) 
{
	if (root == empty) return empty;
	if (val < root->val) root->lf = erase(root->lf, val);
	else if (root->val < val) root->rt = erase(root->rt, val);
	else 
	{
		if (root->lf == empty) return root->rt;
		else if (root->rt == empty) return root->lf;
		else 
		{
			root->priority = -1;
			root = balance(root);
			return erase(root, val);
		}
	}
	root->updateSize();
	return balance(root);
}

inline Node *eraseIdx(Node *root, int idx) 
{
	if (idx < root->lf->s)
		root->lf = eraseIdx(root->lf, idx);
	else if (idx -= root->lf->s + root->frq, idx >= 0) 
		root->rt = eraseIdx(root->rt, idx);
	else if (!--root->frq) 
		root = erase(root, root->val);
	root->updateSize();
	return balance(root);
}

int main() 
{
	// Run Example
	int a;
	scanf("%d ", &a);
	Node *treap = empty;
	while (a--) 
	{
		char c;
		nt k;
		scanf(" %c%d", &c, &k);
		if (c == 'I') 
		{
			int ind = lower_bound(treap, k);
			if (ind != treap->size() && (*treap)[ind] == k) continue;
			treap = insert(treap, k);
		} 
		else if (c == 'D') 
		{
			treap = erase(treap, k);
		} 
		else if (c == 'K') 
		{
			k--;
			if (treap->size() <= k) printf("invalid\n");
			else printf("%d\n", (*treap)[k]);
		} 
		else if (c == 'C') 
		{
			printf("%d\n", lower_bound(treap, k));
		}
	}
	return 0;
}