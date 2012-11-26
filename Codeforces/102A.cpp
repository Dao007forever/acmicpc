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
const int inf = 100000000;
int N, M;
int f[MAXN][MAXN], a[MAXN];

int main()
{
	freopen("a", "r", stdin);
	memset(f, 0, sizeof(f));
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= M; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		f[u][v] = f[v][u] = 1;
	}
	int res = inf;
	bool flag = false;
	for (int k = 1; k <= N; k++)
	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++)
	if (i != k && i != j && j != k)
		if (f[i][k] && f[k][j] && f[i][j])
		{
			flag = true;
			res = min(res, a[i] + a[j] + a[k]);
		}
	if (res != inf) printf("%d\n", res);
	else printf("-1\n");
	return 0;
}
