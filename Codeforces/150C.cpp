/*
 * 线段树，对于每个乘客，求区间[a, b-1]的最大字段和
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
#define lson(t) ((t) << 1)
#define rson(t) (((t) << 1) | 1)
#define maxn 155555

struct Nod {
	int l, r;
	double maxL, maxR, sum, Max;
}T[maxn << 2];
int N, M;
double C;
double x[maxn], p[maxn], a[maxn];

void pushUp(int rt) {
	T[rt].sum = T[lson(rt)].sum + T[rson(rt)].sum;
	T[rt].maxL = max(T[lson(rt)].maxL, T[lson(rt)].sum + T[rson(rt)].maxL);
	T[rt].maxR = max(T[rson(rt)].maxR, T[lson(rt)].maxR + T[rson(rt)].sum);
	T[rt].Max = max(max(T[lson(rt)].Max, T[rson(rt)].Max), T[lson(rt)].maxR + T[rson(rt)].maxL);
}

void build(int l, int r, int rt) {
	T[rt].l = l; T[rt].r = r;
	if (l == r) {
		T[rt].sum = a[r];
		T[rt].Max = max(0.0, a[r]);
		T[rt].maxL = T[rt].maxR = T[rt].Max;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
	pushUp(rt);
}

Nod query(int L, int R, int rt) {
	if (L <= T[rt].l && T[rt].r <= R) {
		return T[rt];
	}
	int mid = (T[rt].l + T[rt].r) >> 1;
	if (R <= mid) return query(L, R, lson(rt));
	else if (L > mid) return query(L, R, rson(rt));
	else {
		Nod ll = query(L, mid, lson(rt));
		Nod rr = query(mid + 1, R, rson(rt));
		Nod tmp;
		tmp.sum = ll.sum + rr.sum;
		tmp.maxL = max(ll.maxL, ll.sum + rr.maxL);
		tmp.maxR = max(rr.maxR, rr.sum + ll.maxR);
		tmp.Max = max(max(ll.Max, rr.Max), ll.maxR + rr.maxL);
		return tmp;
	}
}

int main() {
	freopen("in", "r", stdin);
	cin >> N >> M >> C;
	for (int i = 0; i < N; i++) {
		cin >> x[i];
	}
	for (int i = 1; i < N; i++) {
		cin >> p[i];
		a[i] = (x[i] - x[i - 1]) * 0.5 - C * p[i] / 100.0;
	}
	build(1, N - 1, 1);
	double ret = 0.0;
	while (M--) {
		int x, y;
		cin >> x >> y;
		double tmp = query(x, y - 1, 1).Max;
		if (tmp > 0) ret += tmp;
	}
	printf("%.8lf\n", ret);
	return 0;
}
