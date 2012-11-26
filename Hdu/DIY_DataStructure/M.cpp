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

#define MAXN 100005
int n, q;
struct TNode {
	int l, r;
	LL sum, add;
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
}

void pushDown(int rt, int m) {
	if (T[rt].add) {
		T[lson(rt)].add += T[rt].add;
		T[rson(rt)].add += T[rt].add;
		T[lson(rt)].sum += T[rt].add * (m - (m >> 1));
		T[rson(rt)].sum += T[rt].add * (m >> 1);
		T[rt].add = 0;
	}
}

void build(int l, int r, int rt) {
	T[rt].l = l; T[rt].r = r; T[rt].sum = T[rt].add = 0;
	if (l == r) {
		T[rt].sum = a[l];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
	pushUp(rt);
}

void update(int L, int R, int c, int rt) {
	if (L <= T[rt].l && T[rt].r <= R) {
		T[rt].add += c;
		T[rt].sum += (LL)c * (T[rt].r - T[rt].l + 1);
		return;
	}
	pushDown(rt, T[rt].r - T[rt].l + 1);
	int mid = (T[rt].l + T[rt].r) >> 1;
	if (L <= mid) update(L, R, c, lson(rt));
	if (R > mid) update(L, R, c, rson(rt));
	pushUp(rt);
}

LL query(int L, int R, int rt) {
	if (L <= T[rt].l && T[rt].r <= R) {
		return T[rt].sum;
	}
	pushDown(rt, T[rt].r - T[rt].l + 1);
	int mid = (T[rt].l + T[rt].r) >> 1;
	LL ret = 0;
	if (L <= mid) ret += query(L, R, lson(rt));
	if (R > mid) ret += query(L, R, rson(rt));
	return ret;
}

int main() {
	freopen("M.in", "r", stdin);
	while (scanf("%d%d", &n, &q) != EOF) {
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		build(1, n, 1);
		while (q--) {
			char op[5];
			int a, b, c;
			scanf("%s", op);
			if (*op == 'Q') {
				scanf("%d%d", &a, &b);
				cout << query(a, b, 1) << endl;
			} else {
				scanf("%d%d%d", &a, &b, &c);
				update(a, b, c, 1);
			}
		}
	}
	return 0;
}
