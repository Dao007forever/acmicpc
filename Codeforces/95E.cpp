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

const int MAXN = 100000 + 10;
const int inf = 1000000000;
int N, M;
int p[MAXN], size[MAXN], cnt[MAXN];
int dp[MAXN];

int find(int x)
{
	if (p[x] != x)
		p[x] = find(p[x]);
	return p[x];
}

bool is_lucky(int x)
{
	while (x)
	{
		int tmp = x % 10;
		if (tmp != 4 && tmp != 7) return false;
		x /= 10;
	}
	return true;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		p[i] = i;
	for (int i = 1; i <= M; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		p[find(u)] = find(v);
	}
	for (int i = 1; i <= N; i++)
		size[find(i)]++;
	for (int i = 1; i <= N; i++)
		cnt[size[i]]++;
	fill(dp + 1, dp + N + 1, inf);
	for (int i = 1; i <= N; i++)
	if (cnt[i] > 0)
	{
		int num = cnt[i];
		for (int p = 1; num > 0; p <<= 1)
		{
			p = min(p, num);
			num -= p;
			int w = p * i;
			for (int j = N - w; j >= 0; j--)
				dp[j + w] = min(dp[j + w], dp[j] + p);
		}
	}
	int ans = inf;
	for (int i = 1; i <= N; i++)
	if (is_lucky(i))
		ans = min(ans, dp[i]);
	if (ans == inf) ans = -1;
	else ans--;
	cout << ans << endl;
	return 0;
}
