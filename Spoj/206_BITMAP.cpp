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

const int MAXN = 222;
const int inf = 100000000;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
struct Node
{
	int x, y;
	void init(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};
int n, m;
char g[222][222];
int dis[222][222];

int dist(int x1, int y1, int x2, int y2)
{
	return abs(x1 - x2) + abs(y1 - y2);
}

bool check(int x, int y)
{
	if (g[x][y] == '1') return false;
	if (x >= 1 && x <= n && y >= 1 && y <= m) return true;
	return false;
}

queue<Node> Q;
void bfs(int x, int y)
{
	while (!Q.empty())
		Q.pop();

	dis[x][y] = 0;
	Node tmp;
	tmp.init(x, y);
	Q.push(tmp);
	while (!Q.empty())
	{
		Node cur = Q.front();
		Q.pop();
		for (int k = 0; k < 4; k++)
		{
			int xx = cur.x + dx[k], yy = cur.y + dy[k];
			if (check(xx, yy) && dis[cur.x][cur.y] + 1 < dis[xx][yy])
			{
				dis[xx][yy] = dis[cur.x][cur.y] + 1;
				tmp.init(xx, yy);
				Q.push(tmp);
			}
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				dis[i][j] = inf;
		for (int i = 1; i <= n; i++)
			scanf("%s", g[i] + 1);

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
			if (g[i][j] == '1')
				bfs(i, j);
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
				if (j < m) printf("%d ", dis[i][j]);
				else printf("%d\n", dis[i][j]);
		}
	}
	return 0;
}
