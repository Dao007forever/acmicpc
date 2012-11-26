/*
 * 给一些区间，每个区间有一个价值，要求选出若干个不相交的区间使得它们的价值之和最大
 * 先离散化，然后用线段树优化dp
 */
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

const int maxn = 100005;
struct Order {
	int id, w, t;
}o[maxn];
struct Task {
	int x, y, p;
}ta[maxn];
struct Node {
	int l, r, Max;
}T[maxn << 4];
int N, M;

bool cmp(Order A, Order B)
{
	return A.t < B.t;
}

bool cmpta(Task A, Task B)
{
	return A.x < B.x;
}

inline int lson(int rt)
{
	return rt << 1;
}

inline int rson(int rt)
{
	return rt << 1 | 1;
}

void pushUp(int rt)
{
	T[rt].Max = max(T[lson(rt)].Max, T[rson(rt)].Max);
}

void build(int l, int r, int rt)
{
	T[rt].l = l; T[rt].r = r;
	if (l == r) {
		T[rt].Max = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
	pushUp(rt);
}

int query(int L, int R, int rt)
{
	if (L <= T[rt].l && T[rt].r <= R) {
		return T[rt].Max;
	}
	int mid = (T[rt].l + T[rt].r) >> 1;
	int ret = 0;
	if (L <= mid) ret = max(ret, query(L, R, lson(rt)));
	if (R > mid) ret = max(ret, query(L, R, rson(rt)));
	return ret;
}

void update(int p, int c, int rt)
{
	if (T[rt].l == T[rt].r) {
		T[rt].Max = max(T[rt].Max, c);
		return;
	}
	int mid = (T[rt].l + T[rt].r) >> 1;
	if (p <= mid) update(p, c, lson(rt));
	else update(p, c, rson(rt));
	pushUp(rt);
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> N;
		M = 0;
		for (int i = 0; i < N; i++) {
			int s, d, p;
			cin >> s >> d >> p;
			o[M].id = i; o[M].w = 0; o[M++].t = s;
			o[M].id = i; o[M].w = 1; o[M++].t = s + d - 1;
			ta[i].p = p;
		}
		sort(o, o + M, cmp);

		int k = 1;
		int cur = o[0].t;
		for (int i = 0; i < M; i++) {
			if (cur != o[i].t) {
				k++;
				cur = o[i].t;
			}
			if (o[i].w == 0) {
				ta[o[i].id].x = k;
			} else {
				ta[o[i].id].y = k;
			}
		}
		build(0, k, 1);
		sort(ta, ta + N, cmpta);
		int ret = 0;
		for (int i = 0; i < N; i++) {
			int now = query(0, ta[i].x - 1, 1);
			ret = max(ret, now + ta[i].p);
			update(ta[i].y, now + ta[i].p, 1);
		}
		cout << ret << endl;
	}
	return 0;
}
