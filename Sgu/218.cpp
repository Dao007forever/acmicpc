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

const int maxn = 505;
const int inf = 10000000;
int N, nx, ny;
int a[maxn][maxn], g[maxn][maxn];
int cx[maxn], cy[maxn], mk[maxn], ans[maxn];

int path(int u)
{
        for (int v = 1; v <= ny; v++)
        {
                if (g[u][v] > 0 && (!mk[v]))
                {
                        mk[v] = 1;
                        if (!cy[v] || path(cy[v]))
                        {
                                cx[u] = v;
                                cy[v] = u;
                                return 1;
                        }
                }
        }
        return 0;
}

int MaxMatch()
{
        int res = 0;
        memset(cx, 0, sizeof(cx));
        memset(cy, 0, sizeof(cy));
        for (int i = 1; i <= nx; i++)
        {
                if (!cx[i])
                {
                        memset(mk, 0, sizeof(mk));
                        res += path(i);
                }
        }
        return res;
}

bool check(int lim)
{
	nx = ny = N;
	memset(g, 0, sizeof(g));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (a[i][j] <= lim) {
				g[i][j] = 1;
			}
	int ret = MaxMatch();
	return (ret == N);
}

int main()
{
	freopen("in", "r", stdin);
	cin >> N;
	int Left = inf, Right = -inf;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			cin >> a[i][j];
			if (a[i][j] < Left) Left = a[i][j];
			if (a[i][j] > Right) Right = a[i][j];
		}
	int ret;
	while (Left <= Right) {
		int mid = (Left + Right) >> 1;
		if (check(mid)) {
			ret = mid;
			for (int i = 1; i <= nx; i++)
				ans[i] = cx[i];
			Right = mid - 1;
		}
		else Left = mid + 1;
	}
	cout << ret << endl;
	for (int i = 1; i <= N; i++)
		printf("%d %d\n", i, ans[i]);
}
