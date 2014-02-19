#include <iostream>
#include <list>
#include <map>

using namespace std;

class A
{
	public:
	int x;
	int y;
	A()
	{

	}
};

void fun(list<int> &l)
{
	int x;
	cin >> x;
	l.push_back(x);
	if(x == 0)
		return;	
	fun(l);
}

int main()
{
	list<int> l;
	list<int>::iterator it;
	
	map<int, int> mp;
	map<int, int> :: reverse_iterator mit;

	mp[1] = 100;
	mp[3] = 20;
	mp[5] = 200;
	
	for(mit = mp.rbegin(); mit != mp.rend(); ++mit)
		cout << (*mit).second << endl;
	
	fun(l);
	
	for(it = l.begin(); it != l.end(); ++it)
		cout << endl << *it;
	
	cout << endl;
	list<A> a;
	
	A x;
	x.x = 1;
	return 0;
}
