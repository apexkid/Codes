/*
 * KRUSKAL's ALGORITHM
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
	vector<vector<int> > ds;	//Disjoint set
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
	void getEdges(void);
	void Kruskals(void);
	void printResult(void);

	//ds operations
	void makeset();
	int findset(int x);
	void unionset(int x, int y);
};

void Graph::addEdge(int i, int j, int w)
{
	G[i][j] = w;
	return;
}

void Graph::makeset()
{
	for(int i = 0; i < N; i++)
	{
	 	vector<int> temp2;
	  	for(int j = 0; j < N; j++)
	  	{
	 		if(i == j)
				temp2.push_back(1);
			else
				temp2.push_back(0);
	   	}
	   	ds.push_back(temp2);
	}
}

int Graph::findset(int x)
{
	for(int i = 0; i < N; i++)
	{
		if(ds[x][i] == 1)
			return i;
	}
}

void Graph::unionset(int x, int y)
{
	x = findset(x);
	y = findset(y);
	for(int i = 0; i < N; i++)
	{
		if(ds[i][y] == 1)
		{
			ds[i][x] = 1;
			ds[i][y] = 0;
		}
	}

}

void Graph::getEdges()
{
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(G[i][j])
			{
				Edge e(i, j, G[i][j]);
				Q.push(e);
			}
		}
	}
}

void Graph::Kruskals()
{
	getEdges();
	
	Edge edge(0,0,0);
	int x, y, w;
	
	makeset();

	cout << "in queue" << endl;
	while(!Q.empty())
	{
		edge = Q.top();		Q.pop();
		x = edge.x;
		y = edge.y;
		w = edge.w;
		
		if(findset(x) != findset(y))
		{
			unionset(x, y);
			spt.push_back(edge);
			sum += w;
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

	g.Kruskals();
	g.printResult();

	g.getEdges();

	return 0;
}
