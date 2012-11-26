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
const int inf = 100000000;
struct Point
{
	int x, y;
	int id, ans, py;
	void init() 
	{
		scanf("%d%d", &x, &y);
	}
};
/*struct TNode
{
	int l, r, minp;
	int mid()
	{
		return (l + r) >> 1;
	}
};

struct SegTree
{
	TNode T[MAXN << 2];

	int lson(int rt) {return rt << 1;}
	int rson(int rt) {return (rt << 1) | 1;}

	void build(int l, int r, int rt)
	{
		T[rt].l = l; T[rt].r = r;
		T[rt].minp = inf;
		if (l == r)
		{
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, lson(rt));
		build(mid + 1, r, rson(rt));
		pushUp(rt);
	}

	void pushUp(int rt)
	{
		T[rt].minp = min(T[lson(rt)].minp, T[rson(rt)].minp);
	}

	void update(int p, int c, int rt)
	{
		if (T[rt].l == T[rt].r)
		{
			if (c < T[rt].minp) T[rt].minp = c;
			return;
		}
		int mid = T[rt].mid();
		if (p <= mid) update(p, c, lson(rt));
		else update(p, c, rson(rt));
		pushUp(rt);
	}

	int query(int L, int R, int rt)
	{
		if (R < L) return inf;
		if (L <= T[rt].l && T[rt].r <= R)
		{
			return T[rt].minp;
		}
		int mid = T[rt].mid();
		if (R <= mid) return query(L, R, lson(rt));
		else if (L > mid) return query(L, R, rson(rt));
		else
		{
			return min(query(L, mid, lson(rt)), query(mid + 1, R, rson(rt)));
		}
	}
}Tree1, Tree2;*/

int N;
int tmp[MAXN];
Point ps[MAXN];
struct TreeArray
{
	int t[MAXN];
	int n;

	void init(int n)
	{
		this->n = n;
		for (int i = 1; i <= n; i++)
			t[i] = inf;
	}

	int lowbit(int x)
	{
		return (x & (x ^ (x - 1)));
	}

	int query(int x)
	{
		int tmp = x;
		while (x)
		{
			if (t[x] < t[tmp]) tmp = x;
			x -= lowbit(x);
		}
		return t[tmp];
	}

	void insert(int x, int y)
	{
		while (x <= n)
		{
			if (t[x] > y) t[x] = y;
			x += lowbit(x);
		}
	}
}T1, T2;


bool cmp(const Point &a, const Point &b)
{
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

int find(int x)
{
	int l = 1, r = N;
	while (1)
	{
		int mid = (l + r) >> 1;
		if (tmp[mid] == x) return mid;
		if (x < tmp[mid]) r = mid - 1;
		else l = mid + 1;
	}
}

void solve()
{
	for (int i = 1; i <= N; i++)
		tmp[i] = ps[i].y;
	sort(tmp + 1, tmp + N + 1);
	for (int i = 1; i <= N; i++)
		ps[i].py = find(ps[i].y);
	sort(ps + 1, ps + N + 1, cmp);

	for (int i = 1; i <= N; i++)
		ps[i].ans = inf;
/*	Tree1.build(1, N, 1);
	Tree2.build(1, N, 1);
	for (int i = 1; i <= N; i++)
	{
		int u = Tree1.query(1, ps[i].py, 1);
		int v = Tree2.query(1, N - ps[i].py + 1, 1);
		int tmp = min(u + ps[i].x + ps[i].y, v + ps[i].x - ps[i].y);
		ps[i].ans = min(ps[i].ans, tmp);
		Tree1.update(ps[i].py, -ps[i].x-ps[i].y, 1);
		Tree2.update(N - ps[i].py + 1, -ps[i].x+ps[i].y, 1);
	}
	Tree1.build(1, N, 1);
	Tree2.build(1, N, 1);
	for (int i = N; i >= 1; i--)
	{
		int u = Tree1.query(1, ps[i].py, 1);
		int v = Tree2.query(1, N - ps[i].py + 1, 1);
		int tmp = min(u - ps[i].x + ps[i].y, v - ps[i].x - ps[i].y);
		ps[i].ans = min(ps[i].ans, tmp);
		Tree1.update(ps[i].py, ps[i].x-ps[i].y, 1);
		Tree2.update(N - ps[i].py + 1, ps[i].x+ps[i].y, 1);
	}*/
	T1.init(N);
	T2.init(N);
	for (int i = 1; i <= N; i++)
	{
		int u = T1.query(ps[i].py), v = T2.query(N - ps[i].py + 1);
		int tmp = min(u + ps[i].x + ps[i].y, v + ps[i].x - ps[i].y);
		ps[i].ans = min(ps[i].ans, tmp);
		T1.insert(ps[i].py, -ps[i].x-ps[i].y);
		T2.insert(N - ps[i].py + 1, -ps[i].x+ps[i].y);
	}
	T1.init(N);
	T2.init(N);
	for (int i = N; i >= 1; i--)
	{
		int u = T1.query(ps[i].py), v = T2.query(N - ps[i].py + 1);
		int tmp = min(u - ps[i].x + ps[i].y, v - ps[i].x - ps[i].y);
		ps[i].ans = min(ps[i].ans, tmp);
		T1.insert(ps[i].py, ps[i].x - ps[i].y);
		T2.insert(N - ps[i].py + 1, ps[i].x + ps[i].y);
	}
}

bool cmp2(const Point &a, const Point &b)
{
	return a.id < b.id;
}

void output()
{
	sort(ps + 1, ps + N + 1, cmp2);
	for (int i = 1; i <= N; i++)
		printf("%d\n", ps[i].ans);
}

int main()
{
	freopen("in", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		ps[i].init();
		ps[i].id = i;
	}
	solve();
	output();
	return 0;
}
