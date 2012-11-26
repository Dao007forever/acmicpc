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

const int MAXN = 111111;
int N, Q;
int a[MAXN], x[MAXN], LL[MAXN], RR[MAXN], ll[MAXN], rr[MAXN], H[MAXN], id[MAXN];
int MAX[MAXN << 2];

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
	MAX[rt] = max(MAX[lson(rt)], MAX[rson(rt)]);
}

void build(int l, int r, int rt)
{
	if (l == r)
	{
		MAX[rt] = x[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
	pushUp(rt);
}

int query(int L, int R, int l, int r, int rt)
{
	if (L > R) return 0;
	if (L <= l && r <= R)
	{
		return MAX[rt];
	}
	int mid = (l + r) >> 1;
	int ans = 0;
	if (L <= mid) ans = max(ans, query(L, R, l, mid, lson(rt)));
	if (R > mid) ans = max(ans, query(L, R, mid + 1, r, rson(rt)));
	return ans;
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) && N)
	{
		scanf("%d", &Q);
		for (int i = 1; i <= N; i++)
			scanf("%d", &a[i]);
		int len = 1;
		for (int i = 1; i <= N; i++)
		{
			LL[len] = i;
			int k = 0;
			while (a[i] == a[i + 1])
			{
				i++;
				k++;
			}
			RR[len] = LL[len] + k;
			H[len] = k + 1;
			len++;
		}
		len--;
		int now = a[1], k = 1;
		for (int i = 1; i <= N; i++)
		{
			if (a[i] != now) k++, now = a[i];
			id[i] = k;
			x[i] = H[k];
			ll[i] = LL[k];
			rr[i] = RR[k];
		}
		build(1, N, 1);
		for (int i = 1; i <= Q; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			int ans = 0;
			if (id[a] == id[b])
			{
				printf("%d\n", b - a + 1);
				continue;
			}
			if (ll[a] < a)
			{
				ans = max(ans, rr[a] - a + 1);
				a = rr[a] + 1;
			}
			if (rr[b] > b)
			{
				ans = max(ans, b - ll[b] + 1);
				b = ll[b] - 1;
			}
			if (a <= b) ans = max(ans, query(a, b, 1, N, 1));
			printf("%d\n", ans);
		}
	}
	return 0;
}
