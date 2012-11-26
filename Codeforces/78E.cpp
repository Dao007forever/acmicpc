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
const int inf = 0x3f3f3f3f;
struct SAP
{
    int cap[MAXN][MAXN], flow[MAXN][MAXN], g[MAXN][MAXN];
    int n;
    int h[MAXN], vh[MAXN], source, sink;
    int mk[MAXN];
    void init(int n)
    {
        this->n = n;
        memset(cap, 0, sizeof(cap));
        memset(g, 0, sizeof(g));
        memset(mk, 0, sizeof(mk));
    }
    void addCap(int i, int j, int val)
    {
        cap[i][j] += val;
        g[i][j] = 1;
    }
    int sap(const int idx, const int maxCap)
    {
        if (idx == sink)
            return maxCap;
        int l = maxCap, d, minH = n;
        for (int i = 0; i < n; i++)
        {
            if (cap[idx][i] - flow[idx][i] > 0)
            {
                if (h[idx] == h[i] + 1)
                {
                    d = sap(i, min(l, cap[idx][i] - flow[idx][i]));
                    flow[idx][i] += d;
                    flow[i][idx] -= d;
                    l -= d;
                    if (h[source] == n || l == 0) return maxCap - l;
                }
                minH = min(minH, h[i] + 1);
            }
        }
        if (l == maxCap)
        {
            vh[h[idx]]--;
            vh[minH]++;
            if (vh[h[idx]] == 0)
                h[source] = n;
            h[idx] = minH;
        }
        return maxCap - l;
    }
    int solve(int source, int sink)
    {
        if (source == sink) return inf;
        this->sink = sink;
        this->source = source;
        memset(flow, 0, sizeof(flow));
        memset(h, 0, sizeof(h));
        memset(vh, 0, sizeof(vh));
        int ans = 0;
        while (h[source] != n)
            ans += sap(source, inf);
        return ans;
    }
}sap;
struct Node
{
	int x, y, step;
};

int n, t;
int sx, sy;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
char mat1[MAXN][MAXN], mat2[MAXN][MAXN];
int flag[MAXN][MAXN], vis[MAXN][MAXN];

int ID(int i, int j)
{
	return (i - 1) * n + j;
}

bool check(int x, int y)
{
	if (x < 1 || x > n || y < 1 || y > n) return false;
	return true;
}

void BFS1()
{
	queue<Node> Q;
	Node now, next;
	now.x = sx; now.y = sy; now.step = 0;
	Q.push(now);
	memset(flag, 0x7f, sizeof(flag));
	memset(vis, 0, sizeof(vis));
	vis[now.x][now.y] = 1;
	while (!Q.empty())
	{
		now = Q.front();
		Q.pop();
		flag[now.x][now.y] = now.step;
		if (now.step > t) break;
		for (int k = 0; k < 4; k++)
		{
			int x = now.x + dx[k], y = now.y + dy[k];
			if (check(x, y) && mat1[x][y] != 'Y' && !vis[x][y])
			{
				next.x = x; next.y = y; next.step = now.step + 1;
				vis[x][y] = 1;
				Q.push(next);
			}
		}
	}
}

void BFS2(int i, int j)
{
	queue<Node> Q;
	Node now, next;
	now.x = i; now.y = j; now.step = 0;
	Q.push(now);
	memset(vis, 0, sizeof(vis));
	vis[now.x][now.y] = 1;
	while (!Q.empty())
	{
		now = Q.front();
		Q.pop();
		if (now.step > t) break;
		if (flag[now.x][now.y] < now.step) continue;
		if (flag[now.x][now.y] == now.step && mat2[now.x][now.y] < '1' || mat2[now.x][now.y] > '9') continue;
		if (mat2[now.x][now.y] >= '1' && mat2[now.x][now.y] <= '9')
		{
			if (now.x != i || now.y != j) 
				sap.addCap(ID(i, j), ID(now.x, now.y) + n * n, inf);
			if (flag[now.x][now.y] == now.step) continue;
		}
		for (int k = 0; k < 4; k++)
		{
			int x = now.x + dx[k], y = now.y + dy[k];
			if (check(x, y) && mat1[x][y] != 'Y' && !vis[x][y])
			{
				next.x = x; next.y = y; next.step = now.step + 1;
				vis[x][y] = 1;
				Q.push(next);
			}
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &n, &t);
	for (int i = 1; i <= n; i++)
		scanf("%s", mat1[i] + 1);
	for (int i = 1; i <= n; i++)
		scanf("%s", mat2[i] + 1);
	int source = 0, sink = 2 * n * n + 1;
	sap.init(sink + 1);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (mat1[i][j] >= '1' && mat1[i][j] <= '9')
			{
				sap.addCap(source, ID(i, j), mat1[i][j] - '0');
			}
			if (mat1[i][j] == 'Z')
			{
				sx = i; sy = j;
			}
		}
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			sap.addCap(ID(i, j), ID(i, j) + n * n, inf);
			if (mat2[i][j] >= '1' && mat2[i][j] <= '9')
			{
				sap.addCap(ID(i, j) + n * n, sink, mat2[i][j] - '0');
			}
		}
	}
	BFS1();
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (mat1[i][j] >= '1' && mat1[i][j] <= '9')
				BFS2(i, j);
		}
	}
	int res = sap.solve(source, sink);
	cout << res << endl;
}
