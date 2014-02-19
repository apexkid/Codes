/*
TEST CASE
0 1 0 1 0
1 0 1 0 0
0 1 0 0 1
1 0 0 0 1
0 0 1 1 0

0
*/
#include <iostream>
#include <queue>
#include <cstring>

#define N 5
#define INF 1000

using namespace std;

void BFS(int G[][N], int s);
int main()
{
	int G[N][N];
	int s;
	cout << "Enter graph and souce";
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			cin >> G[i][j];
	
	cin >> s;
	
	BFS(G, s);
}

void BFS(int G[][N], int s)
{
	int mark[N];
	int dist[N];
	int parent[N];

	memset(mark, 0, sizeof(mark));
	memset(dist, INF, sizeof(mark));
	memset(parent, -1, sizeof(mark));

	queue<int> q;

	q.push(s);
	mark[s] = 1;
	dist[s] = 0;

	while(!q.empty())
	{
		int node = q.front();	q.pop();
		
		for(int i = 0; i < N; i++)
		{
			if(G[node][i] && mark[i] == 0)
			{
				mark[i] = 1;
				dist[i] = dist[node] + 1;
				parent[i] = node;
				q.push(i);
			}
		}
	}
	
	for(int i = 0; i < N; i++)
	{
		cout << dist[i] << "  " << parent[i] <<  endl;
	}
}
