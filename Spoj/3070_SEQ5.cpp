#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int Mhash = 7000003;
struct node
{
	int k, next;
}g[1 << 21];
int n, m, L, U;
int prev[1 << 21], p[1 << 21], cnt[1 << 21], hash[Mhash];
long long ans = 0;

void solve()
{
	int a = 1, b = 0, s1 = 0, s2 = L + 1;
	cnt[0] = L + 1;
	for (int i = 1; i <= n; i++)
	{
		if (prev[i])
		{
			cnt[prev[i]] = 0;
			if (prev[i] >= a) s1--;
			if (prev[i] >= b) s2--;
		}
		cnt[i] = 1;
		s1++;
		s2++;
		while (s1 > U)
			s1 -= cnt[a++];
		while (s2 - cnt[b] >= L)
			s2 -= cnt[b++];
		if (a <= b) ans += (long long)(b - a + 1);
	}
	cout << ans << endl;
}

int main()
{
	freopen("in", "r", stdin);
	scanf("%d%d%d", &n, &L, &U);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &p[i]);
	}
	for (int i = 1; i <= n; i++)
	{
		int k = p[i] % Mhash;
		bool flag = true;
		for (int j = hash[k]; j; j = g[j].next)
		if (p[g[j].k] == p[i])
		{
				prev[i] = g[j].k; g[j].k = i; flag = true; break;
		}
		if (flag)
		{
			m++;
			g[m].k = i;
			g[m].next = hash[k];
			hash[k] = m;
		}
	}

	solve();
}
