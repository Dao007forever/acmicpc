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

const int MAXN = 20;
const int inf = 0x3f3f3f3f;

struct KM
{
        int E[MAXN][MAXN], n;
        bool map[MAXN][MAXN];
        bool visx[MAXN], visy[MAXN], vis[MAXN];
        int mate[MAXN];
		int index, ans, arr[MAXN];

		void init(int n)
		{
			this->n = n;
			memset(E, 0, sizeof(E));
			memset(arr, 0, sizeof(arr));
		}

		void addEdge(int i, int j, int k)
		{
			E[i][j] += k;
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
                static int lx[MAXN], ly[MAXN];
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
                ans = 0;
                for (int i = 0; i < n; i++)
                {
                        ans += E[mate[i]][i];
                }
                return ans;
        }

		void dfs(int idx, int val)
		{
			if (idx == n)
			{
				if (val == ans)
				{
					printf("Best Pairing %d\n", index++);
					for (int i = 0; i < n; i++)
					{
						printf("Supervisor %d with Employee %d\n", i + 1, arr[i] + 1);
					}
				}
				return;
			}
			if (val > ans) return;
			for (int i = 0; i < n; i++)
			{
				if (vis[i]) continue;
				vis[i] = true;
				arr[idx] = i;
				dfs(idx + 1, val + E[idx][i]);
				vis[i] = false;
			}
		}

		void output(int idx)
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					E[i][j] = -E[i][j];
				}
			}
			ans = -ans;
			printf("Data Set %d, Best average difference: %.6f\n", idx, (double)ans / (2.0 * n));
			index = 1;
			memset(vis, 0, sizeof(vis));
			dfs(0, 0);
			printf("\n");
		}
};

KM km;
int N;

int main()
{
	freopen("a", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++)
	{
		scanf("%d", &N);
		km.init(N);
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				int tmp;
				scanf("%d", &tmp);
				tmp--;
				km.addEdge(tmp, i, j);
			}
		}
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				int tmp;
				scanf("%d", &tmp);
				tmp--;
				km.addEdge(i, tmp, j);
			}
		}
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				km.E[i][j] *= -1;
			}
		}

		km.solve();
		km.output(cas);
	}
	return 0;
}
