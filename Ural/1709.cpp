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

const int MAXN = 100 + 10;
const int inf = 0x3f3f3f3f;
int N, D, A;
char str[MAXN][MAXN];
int mp[MAXN][MAXN], p[MAXN], res[MAXN][MAXN], dis[MAXN], vis[MAXN], B[MAXN];
int l[MAXN];
struct Point
{
	int from, u, d;
	bool operator<(const Point it) const
	{
		return d > it.d;
	}
};

priority_queue<Point> Que;
void Prim(int root)
{
	memset(l, 0, sizeof(l));
	int cnt = 0;
	for (int i = 1; i <= N; i++)
	if (p[i] == root)
		l[++cnt] = i;

	memset(dis, 0, sizeof(dis));
	for (int i = 1; i <= cnt; i++)
	{
		dis[l[i]] = inf;
	}
	dis[root] = 0;
	Point s;
	s.u = root;
	s.d = 0;
	Que.push(s);
	memset(vis, 0, sizeof(vis));
	for (int k = 0; k < cnt; k++)
	{
		s = Que.top();
		Que.pop();
		int u = s.u;
		vis[u] = 1;
		if (k > 0)
		{
			res[s.from][u] = 1;
			res[u][s.from] = 1;
		}
		for (int i = 1; i <= cnt; i++)
		{
			if (!vis[l[i]] && mp[u][l[i]] < dis[l[i]])
			{
				dis[l[i]] = mp[u][l[i]];
				s.from = u;
				s.u = l[i];
				s.d = dis[l[i]];
				Que.push(s);
			}
		}
	}
}

void dfs(int u, int root)
{
	B[u] = 1;
	p[u] = root;
	for (int i = 1; i <= N; i++)
		if (!B[i] && mp[u][i] == 1)
			dfs(i, root);
}

vector<int> V;
int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	scanf("%d%d", &D, &A);
	for (int i = 1; i <= N; i++)
		scanf("%s\n", str[i]);

	for (int i = 1; i <= N; i++)
		p[i] = i;

	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++)
	{
		if (str[i][j - 1] == '1')
		{
			mp[i][j] = 1;
		}else if (i != j) mp[i][j] = inf;
	}

	memset(B, 0, sizeof(B));
	for (int i = 1; i <= N; i++)
	if (!B[i])
	{
		dfs(i, i);
	}

	memset(res, 0, sizeof(res));
	for (int i = 1; i <= N; i++)
	if (p[i] == i)
	{
		Prim(i);
		V.push_back(i);
	}
	
	int size = V.size();
	for (int i = 1; i < size; i++)
	{
		res[V[i - 1]][V[i]] = 1;
		res[V[i]][V[i - 1]] = 1;
	}

	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++)
	if (mp[i][j] == inf) mp[i][j] = 0;

	char outs[MAXN][MAXN] = {0};
	long long sum = 0;
	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++)
	{
		if (res[i][j] == mp[i][j])
		{
			outs[i][j - 1] = '0';
		}
		else
		{
			if (res[i][j] == 1 && mp[i][j] == 0)
			{
				outs[i][j - 1] = 'a';
				sum += (long long)A;
			}
			else if (res[i][j] == 0 && mp[i][j] == 1)
			{
				outs[i][j - 1] = 'd';
				sum += (long long)D;
			}
		}
	}

	cout << sum / 2 << endl;
	for (int i = 1; i <= N; i++)
	{
		printf("%s\n", outs[i]);
	}
	return 0;
}
