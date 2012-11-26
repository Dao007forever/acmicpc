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

const int MAXN = 500 + 10;
const int inf = 0x7f7f7f7f;
struct Min_Cut
{
	int n;
	int G[MAXN][MAXN];

	void init(int n)
	{
		this->n = n;
		memset(G, 0, sizeof(G));
	}

	void addEdge(int i, int j, int val)
	{
		G[i][j] += val;
		G[j][i] += val;
	}

	int solve()
	{
		static bool vis[MAXN];
		static int addr[MAXN];
		static int d[MAXN];
		int ans = inf, now, pre;

		for (int i = 0; i < n; i++)
			addr[i] = i;
		while (n > 1)
		{
			memset(vis, 0, sizeof(vis));
			memset(d, 0, sizeof(d));
			now = 0;
			for (int i = 0; i < n - 1; i++)
			{
				vis[addr[now]] = true;
				pre = now;
				now = 0;
				for (int j = 0; j < n; j++)
				{
					if (vis[addr[j]]) continue;
					d[j] += G[addr[pre]][addr[j]];
					if (d[j] > d[now]) now = j;
				}
			}
			ans = min(ans, d[now]);
			for (int i = 0; i < n; i++)
				G[addr[i]][addr[pre]] = (G[addr[pre]][addr[i]] += G[addr[now]][addr[i]]);
			addr[now] = addr[--n];
		}
		return ans;
	}
};

Min_Cut mc;

int main()
{
	freopen("a", "r", stdin);
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		mc.init(n);
		int a, b, c;
		for (int i = 0; i < m; i++)
		{
			scanf("%d%d%d", &a, &b, &c);
			mc.addEdge(a, b, c);
		}
		int ans = mc.solve();
		printf("%d\n", ans);
	}
	return 0;
}
