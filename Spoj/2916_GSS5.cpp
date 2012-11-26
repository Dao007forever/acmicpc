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

const int MAXN = 11111;
int n;
int p[MAXN];
struct TNode
{
	int l, r, minp, maxp, sum, lmax, rmax, maxs;
}T[MAXN << 2];

int lson(int rt)
{
	return rt << 1;
}

int rson(int rt)
{
	return (rt << 1) | 1;
}

void pushUp(int rt)
{
	T[rt].sum = T[lson(rt)].sum + T[rson(rt)].sum;
	T[rt].lmax = max(T[lson(rt)].lmax, T[lson(rt)].sum + T[rson(rt)].lmax);
	T[rt].rmax = max(T[rson(rt)].rmax, T[lson(rt)].rmax + T[rson(rt)].sum);
	T[rt].maxs = max(max(T[lson(rt)].maxs, T[rson(rt)].maxs), T[lson(rt)].rmax + T[rson(rt)].lmax);
	T[rt].maxp = max(T[lson(rt)].maxp, T[rson(rt)].maxp);
	T[rt].minp = min(T[lson(rt)].minp, T[rson(rt)].minp);
}

void build(int l, int r, int rt)
{
	T[rt].l = l; T[rt].r = r;
	if (l == r)
	{
		T[rt].lmax = T[rt].rmax = T[rt].sum = T[rt].maxs = p[r] - p[r - 1];
		T[rt].minp = T[rt].maxp = p[r];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
	pushUp(rt);
}



void init()
{
	memset(p, 0, sizeof(p));
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		int a;
		scanf("%d", &a);
		p[i] = p[i - 1] + a;
	}
	build(0, n, 1);
}

int getmin(int L, int R, int rt)
{
	if (L == T[rt].l && T[rt].r == R) return T[rt].minp;
	int mid = (T[rt].l + T[rt].r) >> 1;
	if (R <= mid) return getmin(L, R, lson(rt));
	if (L > mid) return getmin(L, R, rson(rt));
	int u = getmin(L, mid, lson(rt)), v = getmin(mid + 1, R, rson(rt));
	return min(u, v);
}

int getmax(int L, int R, int rt)
{
	if (L == T[rt].l && T[rt].r == R) return T[rt].maxp;
	int mid = (T[rt].l + T[rt].r) >> 1;
	if (R <= mid) return getmax(L, R, lson(rt));
	if (L > mid) return getmax(L, R, rson(rt));
	int u = getmax(L, mid, lson(rt)), v = getmax(mid + 1, R, rson(rt));
	return max(u, v);
}

TNode getsum(int L, int R, int rt)
{
	if (L <= T[rt].l && T[rt].r <= R)
	{
		return T[rt];
	}
	int mid = (T[rt].l + T[rt].r) >> 1;
	if (R <= mid) return getsum(L, R, lson(rt));
	else if (L > mid) return getsum(L, R, rson(rt));
	else
	{
		TNode ll = getsum(L, mid, lson(rt));
		TNode rr = getsum(mid + 1, R, rson(rt));
		TNode tmp;
		tmp.sum = ll.sum + rr.sum;
		tmp.lmax = max(ll.lmax, ll.sum + rr.lmax);
		tmp.rmax = max(rr.rmax, ll.rmax + rr.sum);
		tmp.maxs = max(max(ll.maxs, rr.maxs), ll.rmax + rr.lmax);
		return tmp;
	}
}

void solve()
{
	int m;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		int X1, Y1, X2, Y2;
		int Max = -100000000, u, v;
		scanf("%d%d%d%d", &X1, &Y1, &X2, &Y2);
		u = getmin(X1 - 1, (Y1 - 1 < X2 - 1 ? Y1 - 1 : X2 - 1), 1);
		v = getmax(X2, Y2, 1);
		Max = max(Max, v - u);
		u = getmin(X1 - 1, Y1 - 1, 1);
		v = getmax((Y1 > X2 ? Y1 : X2), Y2, 1);
		Max = max(Max, v - u);
		if (X2 <= Y1)
		{
			int w = getsum(X2, Y1, 1).maxs;
			Max = max(Max, w);
		}
		printf("%d\n", Max);
	}
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		init();
		solve();
	}
}
