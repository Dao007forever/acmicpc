#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 50000 + 10;
struct TNode
{
	int l, r;
	long long Max, add, len;
}T[MAXN << 2];
int N, Q;
long long data[MAXN], S[MAXN];

int lson(int rt)
{
	return rt << 1;
}

int rson(int rt)
{
	return (rt << 1) | 1;
}

long long sum(int l, int r)
{
	long long ans = 0;
	ans = (long long)(l + r) * (r - l + 1) / 2;
	return ans;
}

void pushUp(int rt)
{
	T[rt].Max = max(T[lson(rt)].Max, T[rson(rt)].Max);
}

void pushDown(int rt, int L, int R)
{
	if (T[rt].add)
	{
		T[lson(rt)].add += T[rt].add;
		T[rson(rt)].add += T[rt].add;
		T[lson(rt)].Max += T[rt].add * sum(T[lson(rt)].l - L + 1, T[lson(rt)].r - L + 1);
		T[rson(rt)].Max += T[rt].add * sum(T[rson(rt)].l - L + 1, T[rson(rt)].r - L + 1);
		T[rt].add = 0;
	}
}

void build(int l, int r, int rt)
{
	T[rt].l = l;
	T[rt].r = r;
	T[rt].len = r - l + 1;
	if (l == r)
	{
		T[rt].Max = S[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
	pushUp(rt);
}

void update(int L, int R, int c, int rt)
{
	if (L <= T[rt].l && T[rt].r <= R)
	{
		T[rt].add += c;
		T[rt].Max += (long long)c * sum(T[rt].l - L + 1, T[rt].r - L + 1);
		return;
	}
	pushDown(rt, L, R);
	int mid = (T[rt].l + T[rt].r) >> 1;
	if (L <= mid) update(L, R, c, lson(rt));
	if (R > mid) update(L, R, c, rson(rt));
	pushUp(rt);
}

long long query(int L, int R, int rt)
{
	if (L <= T[rt].l && T[rt].r <= R)
	{
		return T[rt].Max;
	}
	pushDown(rt, L, R);
	int mid = (T[rt].l + T[rt].r) >> 1;
	long long res = -1LL<<45;
	if (L <= mid) res = max(res, query(L, R, lson(rt)));
	if (R > mid) res = max(res, query(L, R, rson(rt)));
	return res;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		cin >> data[i];
		S[i] = S[i - 1] + data[i];
	}
	build(1, N, 1);
	scanf("%d", &Q);
	for (int i = 1; i <= Q; i++)
	{
		int op, x, y, k;
		scanf("%d", &op);
		if (op == 0)
		{
			scanf("%d%d%d", &x, &y, &k);
			update(x, y, k, 1);
		}
		else
		{
			scanf("%d%d", &x, &y);
			int ans = query(x, y, 1);
			cout << ans << endl;
		}
	}
	return 0;
}
