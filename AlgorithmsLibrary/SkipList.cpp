#include<stdio.h>
#include<stdlib.h>
#include<time.h>

template <class T>
class SkipList
{
	struct SkipNode 
	{
		T value;
		int count;
		int level;
		SkipNode* next;
		SkipNode* down;
		SkipNode(int level, SkipNode* next, SkipNode* down) : 
			level(level), next(next), down(down)
		{
			count = 1;
		}
	};

	SkipNode* head;
	int size;

public:

	SkipList() 
	{
		head = new SkipNode(0, NULL, NULL);
		srand(time(NULL));
		size = 0;
	}

	int randomizeLevel() 
	{
		int level = 0;
		while (level <= head->level && ((double)rand() / (double)RAND_MAX)  < 0.5)
			++level;
		return level;
	}

	int add(T val) 
	{
		if (search(val))
			return increment(val);
		int level = randomizeLevel();
		if (level > head->level) 
			head = new SkipNode(level, NULL, head);
		SkipNode* cur = head;
		SkipNode* last = NULL;
		while (cur != NULL) 
		{
			if (cur->next == NULL || cur->next->value > val) 
			{
				if (level >= cur->level) 
				{
					SkipNode* toAdd = new SkipNode(cur->level, cur->next, NULL);
					toAdd->value = val;
					if (last != NULL)
						last->down = toAdd;
					cur->next = toAdd;
					last = toAdd;
				}
				cur = cur->down;
				continue;
			}
			cur = cur->next;
		}
		++size;
		return 1;
	}

	bool search(T val) 
	{
		SkipNode cur = head;
		while (cur != null) 
		{
			if (cur->next == null || cur->next->value > val) 
			{
				cur = cur->down;
				continue;
			}
			else if (cur->next->value == val)
				return true;
			cur = cur->next;
		}
		return false;
	}

	int increment(T val) 
	{
		SkipNode* cur = head;
		while (true) 
		{
			if (cur->next == null || cur->next->value > val) 
			{
				cur = cur.down;
				continue;
			}
			else if (cur->next->value == val) 
				return ++cur.next.count;
			cur = cur.next;
		}
	}

	void print() 
	{
		SkipNode* cur = head;
		SkipNode* first = head;
		while (first != null) 
		{
			cur = first;
			printf("%d ", first->level);
			while (cur != null) 
			{
				printf("%d ", cur->value);
				cur = cur->next;
			}
			putchar('\n');
			first = first->down;
		}
	}

};

int main()
{
	SkipList<int> L;


	return 0;
}
