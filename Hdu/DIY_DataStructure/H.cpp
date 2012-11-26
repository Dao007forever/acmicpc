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

#define MAXN 50005
struct TNode {
	int l, r, max, sum;
}T[MAXN << 2];
int a[MAXN];

inline int lson(int rt) {
	return rt << 1;
}

inline int rson(int rt) {
	return rt << 1 | 1;
}

void pushUp(int rt) {
	T[rt].sum = T[lson(rt)].sum + T[rson(rt)].sum;
	T[rt].max = max(T[lson(rt)].max, T[rson(rt)].max);
}

void build(int l, int r, int rt) {
	T[rt].l = l; T[rt].r = r; T[rt].sum = T[rt].max = 0;
	if (l == r) {
		T[rt].max = T[rt].sum = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
	pushUp(rt);
}

void update(int p, int c, int rt) {
	if (T[rt].l == T[rt].r) {
		T[rt].sum += c;
		T[rt].max += c;
		return;
	}
	int mid = (T[rt].l + T[rt].r) >> 1;
	if (p <= mid) update(p, c, lson(rt));
	else update(p, c, rson(rt));
	pushUp(rt);
}

int querySum(int L, int R, int rt) {
	if (L <= T[rt].l && T[rt].r <= R) {
		return T[rt].sum;
	}
	int mid = (T[rt].l + T[rt].r) >> 1;
	int ret = 0;
	if (L <= mid) ret += querySum(L, R, lson(rt));
	if (R > mid) ret += querySum(L, R, rson(rt));
	return ret;
}

int queryMax(int L, int R, int rt) {
	if (L <= T[rt].l && T[rt].r <= R) {
		return T[rt].max;
	}
	int mid = (T[rt].l + T[rt].r) >> 1;
	int ret = 0;
	if (L <= mid) ret = max(ret, queryMax(L, R, lson(rt)));
	if (R > mid) ret = max(ret, queryMax(L, R, rson(rt)));
	return ret;
}

int main() {
	freopen("H.in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		int n;
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		build(1, n, 1);
		int m;
		scanf("%d", &m);
		while (m--) {
			char op[5];
			scanf("%s", op);
			if (*op == 'Q') {
				int l, r;
				scanf("%d%d", &l, &r);
				int s = querySum(l, r, 1), m = queryMax(l, r, 1);
				printf("%d %d\n", s, m);
			} else {
				int p, x;
				scanf("%d%d", &p, &x);
				if (*op == 'D') x = -x;
				if (a[p] + x < 0) continue;
				a[p] += x;
				update(p, x, 1);
			}
		}
	}
	return 0;
}
