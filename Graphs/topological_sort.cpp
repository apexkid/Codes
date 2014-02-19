/*
 * TOPOLOGICAL SORT
TEST CASE 
6

0 1
0 2
2 1
1 3
3 2
4 3
5 5
-1 -1
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <stack>

#define INF -1

using namespace std;

class Graph
{
	int N;
	vector<vector<int> > G;
	vector<int> dt;		//discovery time
	vector<int> ft;		//finish time
	stack<int> sort_stack;	//Sorted order for topological sort
	int time;
	
	public:
	Graph(int n)
	{
		this -> time = 0;
		this -> N = n;
		for(int i = 0; i < N; i++)
		{
			dt.push_back(INF);
			ft.push_back(INF);
			vector<int> temp;
			for(int j = 0; j < N; j++)
				temp.push_back(0);
				
			G.push_back(temp);
		}
	}
	
	void addEdge(int i, int j);
	void DFS();
	void DFS_visit(int node, bool visited[]);
	void printResult(void);
	void Topological_order(int node);
};

void Graph::addEdge(int i, int j)
{
	G[i][j] = 1;
	return;
}

void Graph::DFS()
{
	bool *visited = new bool[N];
	for(int i = 0; i < N; i++)
		visited[i] = false;
	
	for(int s = 0; s < N; s++)
	{
		if(visited[s] == false)
			DFS_visit(s, visited);
	}
}

void Graph::DFS_visit(int s, bool visited[])
{
	time++;
	dt[s] = time;
	visited[s] = true;
	
	for(int i = 0; i < N; i++)
	{
		if(G[s][i] && !visited[i])
		{
			DFS_visit(i, visited);
		}
	}
	time++;
	ft[s] = time;
	Topological_order(s);
}

void Graph::Topological_order(int s)
{
	sort_stack.push(s);
}

void Graph::printResult()
{
	cout << "vertex" << "  discovery time" << "  finish time" << endl;
	for(int i = 0; i < N; i++)
		cout << i << "               " << dt[i] << "          " << ft[i] << endl;
	
	cout << endl << "Sorted order" << endl;
	for(int i = 0; i < N; i++)
	{
		cout << sort_stack.top() << endl;	sort_stack.pop();
	}
}

int main()
{
	int n;
	cout << "Enter num of vertex" << endl;
	cin >> n;

	Graph g(n);
	
	cout << "Enter the edges.. write -1 -1 to quit" << endl;
	int x , y;
	cin >> x >> y;
	while(x != -1)
	{
		g.addEdge(x, y);
		cin >> x >> y;
	}

	g.DFS();
	g.printResult();
	return 0;
}
