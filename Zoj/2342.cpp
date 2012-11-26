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

const int maxn = 400 + 10;
const int inf = 0x3f3f3f3f;
struct Edge
{
	int u, v, next, c;
}edge[maxn];
int N, M;
int num, Head[maxn];
int cost[maxn], vis[maxn];

struct KM
{
        int E[maxn][maxn], n;
        bool map[maxn][maxn];
        bool visx[maxn], visy[maxn];
        int mate[maxn];

		void addEdge(int i, int j, int k)
		{
			E[i][j] = k;
		}

        bool dfs(int idx)
        {
                visx[idx] = true;
                for (int i = 0; i < n; i++)
                {
                        if (map[idx][i] && !visy[i])
                        {
                                visy[i] = true;
                                if (mate[i] == -1 || dfs(mate[i]))
                                {
                                        mate[i] = idx;
                                        return true;
                                }
                        }
                }
                return false;
        }

        int solve()
        {
                static int lx[maxn], ly[maxn];
                for (int i = 0; i < n; i++)
                {
                        ly[i] = 0;
                        lx[i] = -inf;
                        for (int j = 0; j < n; j++)
                        {
                                lx[i] = max(lx[i], E[i][j]);
                        }
                }
                while (1)
                {
                        for (int i = 0; i < n; i++)
                        for (int j = 0; j < n; j++)
                        {
                                map[i][j] = lx[i] + ly[j] == E[i][j];
                        }
                        memset(mate, 255, sizeof(mate));
                        int i;
                        for (i = 0; i < n; i++)
                        {
                                memset(visx, 0, sizeof(visx));
                                memset(visy, 0, sizeof(visy));
                                if (!dfs(i)) break;
                        }
                        if (i == n)
                        {
                                break;
                        }
                        else
                        {
                                int delta = inf;
                                for (int i = 0; i < n; i++)
                                if (visx[i])
                                {
                                        for (int j = 0; j < n; j++)
                                        {
                                                if (!visy[j])
                                                        delta = min(delta, lx[i] + ly[j] - E[i][j]);
                                        }
                                }
                                for (int i = 0; i < n; i++)
                                {
                                        if (visx[i]) lx[i] -= delta;
                                        if (visy[i]) ly[i] += delta;
                                }
                        }
                }
                int ans = 0;
                for (int i = 0; i < N - 1; i++)
                {
                        ans += E[mate[i]][i];
                }
				/*for (int i = N - 1; i < M; i++)
					printf("%d ", lx[i - N + 1]);
				printf("\n");
				for (int i = 0; i < n; i++)
					printf("%d ", ly[i]);*/
				for (int i = 0; i < N - 1; i++)
					printf("%d\n", cost[i] - lx[i]);
				for (int i = N - 1; i < M; i++)
					printf("%d\n", cost[i] + ly[i - N + 1]);
                return ans;

        }
		void output()
		{
			int ans = solve();
		}

}km;				

void addEdge(int a, int b, int c)
{
	edge[num].v = b;
	edge[num].c = c;
	edge[num].next = Head[a];
	Head[a] = num++;
}

bool dfs(int a, int b, int t, int c)
{
	if (vis[a]) vis[a] = false;
	else return false;
	if (a == b) return true;
	for (int i = Head[a]; i != -1; i = edge[i].next)
	{
		if (dfs(edge[i].v, b, t, c))
		{
			if (c < edge[i].c) 
			{
				km.addEdge(i / 2, t - N + 1, edge[i].c - c);
				//cout << i / 2 << " " << t - n + 1 << " " << edge[i].c - c << endl;
			}
			return true;
		}
	}
	return false;
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		num = 0;
		memset(Head, -1, sizeof(Head));
		scanf("%d%d", &N, &M);
		for (int i = 0; i < N - 1; i++)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			addEdge(a, b, c);
			addEdge(b, a, c);
			cost[i] = c;
		}
		km.n = max(N - 1, M - N + 1);
		memset(km.E, 0, sizeof(km.E));
		for (int i = N - 1; i < M; i++)
		{
			int a, b, c;
			memset(vis, 1, sizeof(vis));
			scanf("%d%d%d", &a, &b, &c);
			dfs(a, b, i, c);
			cost[i] = c;
		}
		km.output();
		if (Test) cout << endl;
	}
	return 0;
}
