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
const int MAX = 100000;
struct KM
{
        int E[maxn][maxn], n;
        bool map[maxn][maxn];
        bool visx[maxn], visy[maxn];
        int mate[maxn];

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
                for (int i = 0; i < n; i++)
                {
                        ans += MAX - E[mate[i]][i];
                }
                return ans;
        }
};

KM km;
int T, N, M;

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &N, &M);
		km.n = N;
		for (int i = 1; i <= M; i++)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			if (MAX - c > km.E[a][b])
				km.E[a][b] = MAX - c;
		}
		printf("%d\n", km.solve());
	}
	return 0;
}
