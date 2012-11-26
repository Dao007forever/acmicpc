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

const int MAXN = 200000 + 10;
struct Seg
{
	int l, r;
	long long p;
}b[MAXN];
int n, m;
long long s[MAXN], dp[MAXN];
long long MAX[MAXN << 2], add[MAXN << 2];

int lson(int rt)
{
	return rt << 1;
}

int rson(int rt)
{
	return (rt << 1) | 1;
}

void build(int l, int r, int rt)
{
	if (l == r)
	{
		add[rt] = MAX[rt] = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
}

void pushDown(int rt)
{
	if (add[rt])
	{
		add[lson(rt)] += add[rt];
		MAX[lson(rt)] += add[rt];

		add[rson(rt)] += add[rt];
		MAX[rson(rt)] += add[rt];

		add[rt] = 0;
	}
}

void pushUp(int rt)
{
	MAX[rt] = max(MAX[lson(rt)], MAX[rson(rt)]);
}

void update(int L, int R, long long c, int l, int r, int rt)
{
	if (L <= l && r <= R)
	{
		add[rt] += c;
		MAX[rt] += c;
		return;
	}
	pushDown(rt);
	int mid = (l + r) >> 1;
	if (L <= mid) update(L, R, c, l, mid, lson(rt));
	if (R > mid) update(L, R, c, mid + 1, r, rson(rt));
	pushUp(rt);
}

bool cmp(const Seg &a, const Seg &b)
{
	return a.r < b.r;
}

int main()
{
	freopen("a", "r", stdin);
	cin >> n >> m;
	s[0] = dp[0] = 0;
	for (int i = 0; i < n; i++)
		cin >> s[i + 1];
	for (int i = 0; i < n; i++)
		s[i + 1] += s[i];
	for (int i = 0; i < m; i++)
		cin >> b[i].l >> b[i].r >> b[i].p;
	sort(b, b + m, cmp);
	build(0, n, 1);
	long long ans = 0;
	for (int i = 1, now = 0; i <= n; i++)
	{
		while (now < m && b[now].r <= i)
		{
			update(0, b[now].l - 1, b[now].p, 0, n, 1);
			now++;
		}
		dp[i] = max(dp[i - 1], MAX[1] - s[i]);
		ans = max(ans, dp[i]);
		update(i, i, dp[i] + s[i], 0, n, 1);
	}
	cout << ans << endl;
}
