#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std; 

const int MAXN = 200 + 10;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
int n, m;
int Map[MAXN][MAXN], mark[MAXN][MAXN];

int ID(int x, int y)
{
	return x * m + y;
}

void Cant()
{
	cout << "No solution" << endl;
	exit(0);
}

int main()
{
	freopen("a", "r", stdin);
	memset(mark, 0, sizeof(mark));
	cin >> n >> m;
	queue<int> Q;
	stack<int> S;
	for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++)
	{
		scanf("%d", &Map[i][j]);
		if (Map[i][j] == 1) 
			Q.push(ID(i, j));
	}

	while (!Q.empty())
	{
		int now = Q.front();
		Q.pop();
		S.push(now);
		int x = now / m, y = now % m;
		mark[x][y] = true;
		for (int k = 0; k < 4; k++)
		{
			int xx = x + dx[k], yy = y + dy[k];
			if (!mark[xx][yy] && xx >= 0 && xx < n && yy >= 0 && yy < m)
			{
				Map[xx][yy]--;
				if (!Map[xx][yy])
				{
					Cant();
				}
				if (Map[xx][yy] == 1)
					Q.push(ID(xx, yy));
			}
		}
	}

	if (S.size() != n * m) Cant();
	while (!S.empty())
	{
		int now = S.top();
		S.pop();
		int x = now / m, y = now % m;
		cout << x + 1 << " " << y + 1 << endl;
	}
	return 0;
}
