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

const int MAXN = 30000 + 10;
int N, M;
int p[MAXN], cnt[MAXN];

int find(int x)
{
	if (x != p[x]) p[x] = find(p[x]);
	return p[x];
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d%d", &N, &M);
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= N; i++)
			p[i] = i;
		for (int i = 1; i <= M; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			int pu = find(u), pv = find(v);
			p[pu] = pv;
		}
		int ans = 0;
		for (int i = 1; i <= N; i++)
			cnt[find(i)]++;
		for (int i = 1; i <= N; i++)
			if (cnt[i] > ans) ans = cnt[i];
		printf("%d\n", ans);
	}
	return 0;
}
