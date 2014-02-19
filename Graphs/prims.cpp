/*
 * PRIM's ALGORITHM
TEST CASE 
9

0 1 4
0 7 8
1 0 4
1 7 11
1 2 8
2 1 8
2 8 2
2 3 7
2 5 4
3 2 7
3 4 9
3 5 14
4 3 9
4 5 10
5 4 10
5 3 14
5 2 4
5 6 2
6 5 2
6 7 1
6 8 6
7 6 1
7 0 8
7 8 7
7 1 11
8 2 2
8 6 6
8 7 7

-1 -1 -1
0
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>

#define INF -1

using namespace std;

class Edge
{
	public:
	int x;
	int y;
	int w;

	Edge(int i, int j, int k)
	{
		this -> x = i;
		this -> y = j;
		this -> w = k;
	}

	bool operator<(const Edge& e) const
	{
		if(w < e.w)
			return false;
		else
			return true;
	}
};

class Graph
{
	int N;
	vector<vector<int> > G;
	priority_queue<Edge> Q;
	vector<Edge> spt;		//Final spanning tree
	int sum;

	public:
	Graph(int n)
	{
		this -> N = n;
		this -> sum = 0;
		for(int i = 0; i < N; i++)
		{
			vector<int> temp;
			for(int j = 0; j < N; j++)
				temp.push_back(0);
				
			G.push_back(temp);
		}
	}
	
	void addEdge(int i, int j, int w);
	void Prims(int source);
	void push_edgesof(int node);
	void printResult(void);

};

void Graph::addEdge(int i, int j, int w)
{
	G[i][j] = w;
	return;
}

void Graph::push_edgesof(int s)
{
	for(int i = 0; i < N; i++)
	{
		Edge e(0,0,0);
		if(G[s][i])
		{
			e.x = s;
			e.y = i;
			e.w = G[s][i];
			Q.push(e);
		}
	}
}

void Graph::Prims(int s)
{
	
	Edge edge(0,0,0);
	int x, y, w;
	
	bool *visited = new bool[N];
	for(int i = 0; i < N; i++)
		visited[N] = false;
	
	push_edgesof(s);
	visited[s] = true;

	while(!Q.empty())
	{
		edge = Q.top();		Q.pop();
		x = edge.x;
		y = edge.y;
		w = edge.w;
		
		if(!visited[y])
		{
			sum += w;
			spt.push_back(edge);
			visited[y] = true;
			push_edgesof(y);
		}
	}
}

void Graph::printResult()
{
	cout << "Total weight of spanning tree = " << sum << endl;
	cout << "Edges in spanning tree" << endl;
	Edge edge(0,0,0);
	for(int i = 0; i < spt.size(); i++)
	{
		edge = spt[i];
		cout << edge.x << "   " << edge.y << "   " << edge.w << endl;
	}
}

int main()
{
	int n;
	cout << "Enter num of vertex" << endl;
	cin >> n;

	Graph g(n);
	
	cout << "Enter the edges with weights.. write -1 -1 to quit" << endl;
	int x , y, w;
	cin >> x >> y >> w;
	while(x != -1)
	{
		g.addEdge(x, y, w);
		cin >> x >> y >> w;
	}
	
	cout << "Enter source vertex" << endl;
	int s;
	cin >> s;

	g.Prims(s);
	g.printResult();

	return 0;
}
