#include <iostream>
#include <queue>

using namespace std;


class Edge { 
	public: 
	int x; int y; int w; 
	Edge(int i, int j, int k) {
		this -> x = i; this -> y = j; this -> w = k; 
	} 
	
	bool operator<(const Edge&) const; 
}; 
bool Edge::operator<(const Edge& e) const { 
	if(this -> w < e.w) 
		return true; 
	else return false; 
}


int main()
{
	Edge a(1,1,1);
	Edge b(2,2,2);
	
	priority_queue<Edge> q;
	if(a < b)
		cout << "A";
	else
		cout << "B";

	return 0;
}
	
