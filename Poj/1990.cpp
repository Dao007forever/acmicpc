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

const int MAXN = 22222;
long long sum[MAXN << 2];
int key[MAXN << 2];
struct Node
{
	int x, v;
}p[MAXN];

bool cmp(Node a, Node b)
{
	return a.v < b.v;
}

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
	key[rt] = key[lson(rt)] + key[rson(rt)];
}

void build(int l, int r, int rt)
{
	sum[rt] = 0;
	key[rt] = 0;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
}

void update(int p, int l, int r, int rt)
{
	if (l == r)
	{
		sum[rt] = p;
		key[rt] = 1;
		return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid) update(p, l, mid, lson(rt));
	else update(p, mid + 1, r, rson(rt));
	pushUp(rt);
}

long long query1(int L, int R, int l, int r, int rt)
{
	if (L <= l && r <= R)
	{
		return sum[rt];
	}
	int mid = (l + r) >> 1;
	long long res = 0;
	if (L <= mid) res += query1(L, R, l, mid, lson(rt));
	if (R > mid) res += query1(L, R, mid + 1, r, rson(rt));
	return res;
}

int query2(int L, int R, int l, int r, int rt)
{
	if (L <= l && r <= R)
	{
		return key[rt];
	}
	int mid = (l + r) >> 1;
	int res = 0;
	if (L <= mid) res += query2(L, R, l, mid, lson(rt));
	if (R > mid) res += query2(L, R, mid + 1, r, rson(rt));
	return res;
}

int main()
{
	freopen("a", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &p[i].v, &p[i].x);
	sort(p + 1, p + n + 1, cmp);

	build(1, MAXN, 1);
	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		long long Sum = query1(1, p[i].x, 1, MAXN, 1);
		int Num = query2(1, p[i].x, 1, MAXN, 1);
		ans += ((long long)Num * p[i].x - Sum) * (long long)p[i].v;
		Sum = query1(p[i].x, MAXN, 1, MAXN, 1);
		Num = query2(p[i].x, MAXN, 1, MAXN, 1);
		ans += (Sum - (long long)Num * p[i].x) * (long long)p[i].v;
		update(p[i].x, 1, MAXN, 1);
	}
	cout << ans << endl;
	return 0;
}
