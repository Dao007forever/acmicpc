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
struct KM
{
        int E[MAXN][MAXN], n, m, slack;
        bool map[MAXN][MAXN];
        bool visx[MAXN], visy[MAXN];
        int mate[MAXN], lx[MAXN], ly[MAXN];

                void init(int n)
                {
                        this->n = n;
                        this->m = n;
                        //memset(E, 0, sizeof(E));
						for (int i = 0; i < n; i++)
							for (int j = 0; j < n; j++)
								E[i][j] = -inf;
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
int N, M;

int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d%d", &N, &M);
		km.init(N);
		for (int i = 1; i <= M; i++)
		{
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			u--; v--;
			km.addEdge(u, v, -w);
			//cout << u << " " << v << " " << w << endl;
		}
		int ans = km.solve();
		printf("%d\n", -ans);
	}
	return 0;
}
