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
const int inf = 0x3f3f3f3f;
struct KM
{
        int E[MAXN][MAXN], n;
        bool map[MAXN][MAXN];
        bool visx[MAXN], visy[MAXN];
        int mate[MAXN];

		void init(int n)
		{
			this->n = n;
			memset(E, 0, sizeof(E));
		}

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
                int ans = 0;
                for (int i = 0; i < n; i++)
                {
                        ans += E[mate[i]][i];
                }
                return ans;
        }
};
KM km;
int N, M;
int data[MAXN], use[MAXN], dis[MAXN][MAXN], L[MAXN], R[MAXN];

int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%d", &data[i]);
		km.init(N);
		memset(dis, -1, sizeof(dis));
		for (int i = 1; i <= N; i++)
			dis[i][i] = 0;
		scanf("%d", &M);
		for (int i = 1; i <= M; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			dis[u][v] = dis[v][u] = 1;
		}
		for (int k = 1; k <= N; k++)
			for (int i = 1; i <= N; i++)
				if (dis[i][k] != -1)
				for (int j = 1; j <= N; j++)
					if (dis[k][j] != -1 && (dis[i][j] == -1 || dis[i][k] + dis[k][j] < dis[i][j]))
						dis[i][j] = dis[i][k] + dis[k][j];
		memset(use, 0, sizeof(use));
		for (int i = 1; i <= N; i++)
			use[data[i]] = 1;
		int n = 0;
		for (int i = 1; i <= N; i++)
			if (!use[i]) R[n++] = i;
		n = 0;
		for (int i = 1; i <= N; i++)
			if (!use[data[i]]) L[n++] = data[i];
			else use[data[i]] = 0;
		if (n == 0)
		{
			printf("0\n");
			continue;
		}
		km.n = n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (dis[L[i]][R[j]] != -1)
				{
					km.addEdge(i, j, -dis[L[i]][R[j]]);
//					cout << i << " " << j << " " << dis[L[i]][R[j]] << endl;
				}
		int res = km.solve();
		printf("%d\n", -res);
	}
	return 0;
}
