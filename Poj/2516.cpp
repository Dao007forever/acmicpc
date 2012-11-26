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

const int MAXN = 55 * 3;
const int inf = 0x3f3f3f3f;
int N, M, K;
int need[55][55], have[55][55], cost[55][55][55], A[MAXN], B[MAXN];
struct KM
{
        int E[MAXN][MAXN], n, m, slack;
        bool map[MAXN][MAXN];
        bool visx[MAXN], visy[MAXN];
        int mate[MAXN], lx[MAXN], ly[MAXN];

                void init(int n, int m)
                {
                        this->n = n;
                        this->m = m;
                        memset(E, 0, sizeof(E));
                }

                void addEdge(int i, int j, int k)
                {
                        E[i][j] = k;
                }

                bool path(int x)
                {
                        visx[x] = true;
                        for (int y = 0; y < m; y++)
                        {
                                if (visy[y]) continue;
                                int t = lx[x] + ly[y] - E[x][y];
                                if (t == 0)
                                {
                                        visy[y] = true;
                                        if (mate[y] == -1 || path(mate[y]))
                                        {
                                                mate[y] = x;
                                                return true;
                                        }
                                }
                                else if (slack > t) slack = t;
                        }
                        return false;
                }

                int solve()
                {
                        memset(mate, -1, sizeof(mate));
                        memset(lx, 0, sizeof(lx));
                        memset(ly, 0, sizeof(ly));
                        for (int x = 0; x < n; x++)
                                for (int y = 0; y < m; y++)
                                        if (E[x][y] > lx[x]) lx[x] = E[x][y];
                        for (int x = 0; x < n; x++)
                        {
                                while (1)
                                {
                                        memset(visx, 0, sizeof(visx));
                                        memset(visy, 0, sizeof(visy));
                                        slack = inf;
                                        if (path(x)) break;
                                        for (int i = 0; i < n; i++)
                                                if (visx[i]) lx[i] -= slack;
                                        for (int i = 0; i < m; i++)
                                                if (visy[i]) ly[i] += slack;
                                }
                        }
                        int ans = 0;
                        for (int y = 0; y < m; y++)
                        if (mate[y] != -1)
                                ans += E[mate[y]][y];
                        return ans;
                }
};

KM km;

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d%d", &N, &M, &K) != EOF)
	{
		if (N == 0 && M == 0 && K == 0) break;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < K; j++)
			{
				scanf("%d", &need[i][j]);
				//printf("%dneed\n", need[i][j]);
			}
		for (int i = 0; i < M; i++)
			for (int j = 0; j < K; j++)
			{
				scanf("%d", &have[i][j]);
				//printf("%dhave\n", have[i][j]);
			}
		for (int k = 0; k < K; k++)
			for (int i = 0; i < N; i++)
				for (int j = 0; j < M; j++)
				{
					scanf("%d", &cost[k][i][j]);
					//printf("%dcost\n", cost[k][i][j]);
				}

		bool ok = true;
		for (int i = 0; i < K; i++)
		{
			int allNeed = 0, allHave = 0;
			for (int j = 0; j < N; j++)
				allNeed += need[j][i];
			for (int j = 0; j < M; j++)
				allHave += have[j][i];
			if (allNeed > allHave)
			{
				ok = false;
				printf("-1\n");
				break;
			}
		}
		if (!ok) continue;
		int ans = 0;
		for (int k = 0; k < K; k++)
		{
			int X = 0, Y = 0;
			for (int i = 0; i < N; i++)
				for (int j = 1; j <= need[i][k]; j++)
					A[X++] = i;
			for (int i = 0; i < M; i++)
				for (int j = 1; j <= have[i][k]; j++)
					B[Y++] = i;
			km.init(X, Y);
			for (int i = 0; i < X; i++)
				for (int j = 0; j < Y; j++)
				{
					km.addEdge(i, j, -cost[k][A[i]][B[j]]);
					//cout << i << " " << j << cost[k][A[i]][B[j]] << endl;
				}
			ans += -km.solve();
		}
		printf("%d\n", ans);
	}
	return 0;
}
