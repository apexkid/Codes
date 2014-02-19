#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <queue>
#include <cmath>
#include <map>
#include <cstdio>
#include <set>
using namespace std;

int a[101][101];
int b[101][101];
int n,m;

struct node
{
	int sx,sy;
	int value;
	int moves;
	string b;
};

typedef struct node node;

bool operator<(struct node a, struct node b)
{
	if (a.moves != b.moves) {
		return a.moves>b.moves;
	}
	return a.value<b.value;
}

void print (int flag) 
{
	int i,j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (flag == 0) {
				cout << b[i][j];
			} else {
				cout << a[i][j];
			}
		}cout << endl;
	}cout << endl;
}

struct node get (int sx, int sy, int value, int moves, string b)
{
	//cout << "SDADSA " << sx << " " << sy << " " << value << " " << moves << " " << b << endl;
	struct node s;
	s.sx = sx;
	s.sy = sy;
	s.value = value;
	s.moves = moves;
	s.b = b;
	return s;
}

int ff (int x, int y)
{
	if (x == 1) {
		return y;
	}
	return 0;
}

int aa[] = {-1, 1, 0, 0};
int bb[] = {0, 0, 1, -1};

bool find (string b, int x)
{
	stringstream is(b);	
	int xx;
	while (is >> xx) {
		if (x == xx) {
			return true;
		}
	}
	return false;
}

string convert (int x)
{
	stringstream is;
	is << x;
	return is.str();
}

void f ()
{
	cout << "Printing the value matrix" << endl;
	print (0);
	cout << "Printing the cost matrix" << endl;
	print (1);
	
	priority_queue <struct node> p;
	p.push (get (0, 0, ff (a[0][0], b[0][0]), 1, "0"));

	string result;
	
	while (p.size()) {
		struct node s = p.top();	p.pop();
		int sx,sy,px,py,i;
		sx = s.sx;	sy = s.sy;
		//cout << sx << " " << sy << " " << s.value << " " << s.moves << " " << " ASDAS " << s.b << endl;
		if (sx == n-1 && sy == m-1) {		
			result = s.b;
			break;
		}
		for (i = 0; i < 4; i++) {	
			px = sx + aa[i];
			py = sy + bb[i];	
			if (px < 0 || py < 0 || px == n || py == m) {
				continue;
			}
			if (find (s.b, b[px][py])) {
				continue;
			}
			p.push (get (px, py, s.value + ff (a[px][py], b[px][py]) ,s.moves+1, s.b + " "  + convert (b[px][py])));
		}

	}

	cout << result << endl;
}


int main()
{
	// Fast input
	freopen ("input.txt", "r", stdin);
	int i,j,ii=0;
	cin >> n >> m;
	
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			cin >> a[i][j];
			b[i][j] = ii++;		
		}
	}

	f();

	return 0;
}
