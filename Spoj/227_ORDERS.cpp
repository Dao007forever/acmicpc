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

const int MAXN = 222222;
const int inf = 100000000;
int a[MAXN];
int sum[MAXN << 2], key[MAXN << 2], ans[MAXN];

int lson(int rt)
{
	return rt << 1;
}

int rson(int rt)
{
	return rt << 1 | 1;
}

void pushUp(int rt)
{
	sum[rt] = sum[lson(rt)] + sum[rson(rt)];
}

void build(int l, int r, int rt)
{
	if (l == r)
	{
		sum[rt] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
	pushUp(rt);
}

int query(int k, int l, int r, int rt)
{
	if (l == r)
	{
		return l;
	}
	int mid = (l + r) >> 1;
	if (k <= sum[lson(rt)]) return query(k, l, mid, lson(rt));
	else return query(k - sum[lson(rt)], mid + 1, r, rson(rt));
}

void update(int p, int l, int r, int rt)
{
	if (l == r)
	{
		sum[rt] = 0;
		return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid) update(p, l, mid, lson(rt));
	else update(p, mid + 1, r, rson(rt));
	pushUp(rt);
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);

		build(1, n, 1);
		for (int i = n; i >= 1; i--)
		{
			int tmp = query(i - a[i], 1, n, 1);
			ans[i] = tmp;
			update(tmp, 1, n, 1);
		}
		for (int i = 1; i <= n; i++)
		{
			if (i == n) printf("%d\n", ans[i]);
			else printf("%d ", ans[i]);
		}
	}
	return 0;
}
