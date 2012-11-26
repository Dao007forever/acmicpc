/*
 *		Problem 	: ACM World Final 2006 problem J, 'Routing'
 *		Coder 		: Guo Huayang from Changjun Senior School
 *		Test By		: CII online judge
 *		Algorithm	: 
 *			f[i][j] stands for minimum node necessary for travel from 0 to i
 *			and from j to 0.
 *			g[i][j] stands for minimum node necessary for travel from i to j
 *		Implementation	:
 *			f[i][j] + g[i][j] - 1 	-> 	f[j][i] holds.
 *			f[i][j] + g[i][k]		->	f[k][j] holds.
 *			f[i][j] + g[k][j]		->	f[i][k] holds.
 *			Floyd is used to compute g.  
 *			Bellman-Ford is used to compute f.
 */
 
#include <cstdio>
#include <iostream>
#include <deque>

using namespace std;

const int infinite = 1000000;

int n, m, f[100][100], g[100][100];
bool used[10000];
deque<int> queue;

void refresh(int i, int j, int cost)
{
	if (cost >= f[i][j]) return;
	f[i][j] = cost;
	if (used[i * n + j]) return;
	used[i * n + j] = 1;
	queue.push_back(i * n + j);
};

int main()
{
	freopen("in", "r", stdin);
	int nowCase = 0;
	while (cin >> n >> m, nowCase ++, n || m)
	{
		for (int i = 0; i < n; i ++)
			for (int j = 0; j < n; j ++)
				f[i][j] = infinite, g[i][j] = infinite;
		
		for (int i = 0; i < m; i ++)
		{
			int x, y;
			cin >> x >> y;
			g[--x][--y] = 1;
		};
		
		for (int k = 0; k < n; k ++)	//	Floyd to get g
			for (int i = 0; i < n; i ++)
				for (int j = 0; j < n; j ++)
					g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
		
		f[0][0] = 1; used[0] = 1;
		queue.clear(); queue.push_back(0);
		while (!queue.empty())	//	Bellman-Ford to get f
		{
			int x = queue.front() / n, y = queue.front() % n;
			used[queue.front()] = 0;
			queue.pop_front();
			
			if (f[x][y] >= f[1][1]) continue;

			refresh(y, x, f[x][y] + g[x][y] - 1);
			
			for (int k = 0; k < n; k ++)
			{
				refresh(k, y, f[x][y] + g[x][k] - (k == y));
				refresh(x, k, f[x][y] + g[k][y] - (k == x));
			};			
		};
		
		cout << "Network " << nowCase << endl;
		if (f[1][1] > n) cout << "Impossible\n";
		else cout << "Minimum number of nodes = " << f[1][1] << endl;
		cout << endl;
	};
};

