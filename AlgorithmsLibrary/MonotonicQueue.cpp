template <class T>
struct monotonic_queue {
	deque<T> q1;
	deque<T> q2;
	T pop()
	{
		T ans = q1.front();
		if(ans == q2.front())
			q2.pop_front();
		q1.pop_front();
		return ans;
	}
	void push(T i)
	{
		while(q2.size() && q2.back() < i)
			q2.pop_back();
		q2.push_back(i);
		q1.push_back(i);
	}
	T max()
	{
		return q2.front();
	}
	T size() 
	{
		return q1.size();
	}
};