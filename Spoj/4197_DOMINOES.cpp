/*
 * Author : Yang Zhang
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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;
#define x first
#define h second
#define MAXN 100005
const int inf = 2000000000;
struct SegTree {
	struct TNode {
		int l, r, min, add;
	}T[MAXN << 2];

	int lson(int rt) {
		return rt << 1;
	}

	int rson(int rt) {
		return (rt << 1) | 1;
	}

	void pushUp(int rt) {
		T[rt].min = min(T[lson(rt)].min, T[rson(rt)].min);
	}

	void pushDown(int rt) {
		if (T[rt].add) {
			T[lson(rt)].add = 1;
			T[rson(rt)].add = 1;
			T[lson(rt)].min = min(T[lson(rt)].min, T[rt].min);
			T[rson(rt)].min = min(T[rson(rt)].min, T[rt].min);
			T[rt].add = 0;
		}
	}

	void build(int l, int r, int rt) {
		T[rt].l = l; T[rt].r = r; T[rt].min = inf; T[rt].add = 0;
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, lson(rt));
		build(mid + 1, r, rson(rt));
	}

	void update(int L, int R, int c, int rt) {
		if (L <= T[rt].l && T[rt].r <= R) {
			T[rt].add = 1;
			T[rt].min = min(T[rt].min, c);
			return;
		}
		pushDown(rt);
		int mid = (T[rt].l + T[rt].r) >> 1;
		if (L <= mid) update(L, R, c, lson(rt));
		if (R > mid) update(L, R, c, rson(rt));
		pushUp(rt);
	}

	int query(int L, int R, int rt) {
		if (L <= T[rt].l && T[rt].r <= R) {
			return T[rt].min;
		}
		pushDown(rt);
		int mid = (T[rt].l + T[rt].r) >> 1;
		int ret = inf;
		if (L <= mid) ret = min(ret, query(L, R, lson(rt)));
		if (R > mid) ret = min(ret, query(L, R, rson(rt)));
		return ret;
	}
}tf, tg;

pair<int, int> p[MAXN];
int n, Left[MAXN], Right[MAXN], tmp[MAXN];
int f[MAXN], g[MAXN];

void work() {
	for (int i = 1; i <= n; i++) {
		Left[i] = i; Right[i] = i;
	}
	int top;
	tmp[1] = 1; top = 1;
	for (int i = 2; i <= n; i++) {
		while (top && p[tmp[top]].x >= p[i].x - p[i].h) {
			Left[i] = Left[tmp[top]];
			top--;
		}
		top++;
		tmp[top] = i;
	}

	tmp[1] = n; top = 1;
	for (int i = n - 1; i >= 1; i--) {
		while (top && (p[tmp[top]].x <= p[i].x + p[i].h)) {
			Right[i] = Right[tmp[top]];
			top--;
		}
		top++;
		tmp[top] = i;
	}
}

void DP() {
	tf.build(1, n, 1);
	tg.build(1, n, 1);
	f[1] = 1; g[1] = 1;
	tf.update(1, 1, f[1], 1);
	tg.update(1, Right[1], g[1], 1);
	for (int i = 2; i <= n; i++) {
		int tmp;
		f[i] = min(g[i - 1], f[i - 1]) + 1;
		tmp = tf.query(Left[i], i, 1);
		f[i] = min(f[i], tmp);

		g[i] = min(g[i - 1], f[i - 1]) + 1;
		tmp = tg.query(i, i, 1);
		g[i] = min(g[i], tmp);

		tf.update(i, i, f[i], 1);
		tg.update(i, Right[i], g[i], 1);
	}
	printf("%d\n", min(f[n], g[n]));
}

int main() {
	freopen("in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &p[i].x, &p[i].h);
	sort(p + 1, p + n + 1);
	work();
	DP();
	return 0;
}
