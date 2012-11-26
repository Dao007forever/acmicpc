#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const double inf = 1000000000;
struct Node
{
	int x, y;
};
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
char p[55][55];
int dist[55][55], value[55];
int n, m, sx, sy, tx, ty;
int res, cnt;

int cost(int x1, int y1, int x2, int y2)
{
	if (p[x1][y1] == '$' || p[x2][y2] == '$') return 2;
	if (p[x1][y1] == p[x2][y2]) return 1;
	if (abs(p[x1][y1] - p[x2][y2]) == 1) return 3;
	return inf;
}

int BFS()
{
	for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++)
		dist[i][j] = inf;
	dist[sx][sy] = 0;
	Node cur;
	cur.x = sx, cur.y = sy;
	queue<Node> que;
	que.push(cur);
	while (!que.empty())
	{
		Node now = que.front();
		que.pop();
		for (int k = 0; k < 4; k++)
		{
			int x = now.x + dx[k], y = now.y + dy[k];
			if (x >= 0 && x < n && y >= 0 && y < m && dist[now.x][now.y] + cost(now.x, now.y, x, y) < dist[x][y])
			{
				dist[x][y] = dist[now.x][now.y] + cost(now.x, now.y, x, y);
				cur.x = x; cur.y = y;
				que.push(cur);
			}
		}
	}
	return dist[tx][ty];
}

void dfs(int now, int s1, int m1, int s2, int m2)
{
	if (max(s1 - m1, s2 - m2) >= res) return;
	if (now == cnt)
	{
		res = max(s1 - m1, s2 - m2);
		return;
	}
	dfs(now + 1, s1 + value[now] * 2, max(m1, value[now]), s2, m2);
	dfs(now + 1, s1, m1, s2 + value[now] * 2, max(m2, value[now]));
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%s", p[i]);
		for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		if (p[i][j] == 'X')
		{
			sx = i; sy = j;
			p[i][j] = '$';
		}

		cnt = 0;
		for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		if (p[i][j] == '$' && (i != sx || j != sy))
		{
			tx = i; ty = j;
			value[cnt++] = BFS();
		}

		bool flag = true;
		for (int i = 0; flag && i < cnt; i++)
		if (value[i] == inf)
		{
			printf("-1\n");
			flag = false;
		}
		if (flag)
		{
			res = inf;
			dfs(0, 0, 0, 0, 0);
			printf("%d\n", res);
		}
	}
	return 0;
}
