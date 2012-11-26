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
const int inf = 1000000000;
struct TNode {
	int l, r, max, add;
}T[MAXN << 2];
int n, m;
int a[MAXN];

inline int lson(int rt) {
	return rt << 1;
}

inline int rson(int rt) {
	return rt << 1 | 1;
}

void pushUp(int rt) {
	T[rt].max = max(T[lson(rt)].max, T[rson(rt)].max);
}

void pushDown(int rt) {
	if (T[rt].add) {
		T[lson(rt)].add += T[rt].add;
		T[rson(rt)].add += T[rt].add;
		T[lson(rt)].max += T[rt].add;
		T[rson(rt)].max += T[rt].add;
		T[rt].add = 0;
	}
}

void build(int l, int r, int rt) {
	T[rt].l = l; T[rt].r = r; T[rt].max = -inf; T[rt].add = 0;
	if (l == r) {
		T[rt].max = a[l];
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
		T[rt].max += c;
		return;
	}
	int mid = (T[rt].l + T[rt].r) >> 1;
	pushDown(rt);
	if (L <= mid) update(L, R, c, lson(rt));
	if (R > mid) update(L, R, c, rson(rt));
	pushUp(rt);
}

int query(int L, int R, int rt) {
	if (L <= T[rt].l && T[rt].r <= R) {
		return T[rt].max;
	}
	int mid = (T[rt].l + T[rt].r) >> 1;
	pushDown(rt);
	int ret = -inf;
	if (L <= mid) ret = max(ret, query(L, R, lson(rt)));
	if (R > mid) ret = max(ret, query(L, R, rson(rt)));
	pushUp(rt);
	return ret;
}

int main() {
	freopen("I.in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		build(1, n, 1);
		while (m--) {
			char op[10];
			scanf("%s", op);
			if (*op == 'u') {
				int l, r, c;
				scanf("%d%d%d", &l, &r, &c);
				update(l, r, c, 1);
			} else if (*op == 'c') {
				int i, j;
				scanf("%d%d", &i, &j);
				int p = query(i, i, 1), q = query(j, j, 1);
				update(i, i, q - p, 1);
				update(j, j, p - q, 1);
			} else {
				int x;
				scanf("%d", &x);
				int l = 1, r = n, ret = n;
				if (T[1].max < x) {
					cout << -1 << endl;
					continue;
				}
				while (l <= r) {
					int mid = (l + r) >> 1;
					if (query(mid, n, 1) >= x) {
						ret = mid;
						l = mid + 1;
					} else r = mid - 1;
				}
				cout << ret << endl;
			}
		}
	}
	return 0;
}
