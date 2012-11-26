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
struct SegTree {
	struct node {
		int l, r, max;
	}T[MAXN << 2];

	int lson(int rt) {
		return rt << 1;
	}

	int rson(int rt) {
		return rt << 1 | 1;
	}

	void pushUp(int rt) {
		T[rt].max = max(T[lson(rt)].max, T[rson(rt)].max);
	}

	void build(int l, int r, int rt) {
		T[rt].l = l; T[rt].r = r; T[rt].max = 0;
		if (l == r) {
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, lson(rt));
		build(mid + 1, r, rson(rt));
	}

	void update(int p, int c, int rt) {
		if (T[rt].l == T[rt].r) {
			T[rt].max = max(T[rt].max, c);
			return;
		}
		int mid = (T[rt].l + T[rt].r) >> 1;
		if (p <= mid) update(p, c, lson(rt));
		else update(p, c, rson(rt));
		pushUp(rt);
	}

	int query(int L, int R, int rt) {
		if (L > R) return 0;
		if (L <= T[rt].l && T[rt].r <= R) {
			return T[rt].max;
		}
		int mid = (T[rt].l + T[rt].r) >> 1;
		int ret = 0;
		if (L <= mid) ret = max(ret, query(L, R, lson(rt)));
		if (R > mid) ret = max(ret, query(L, R, rson(rt)));
		return ret;
	}
}tree;

int n, m;
int h[MAXN], g[MAXN], dp[MAXN];
vector<int> ha;

int Bin(int x) {
	int l = 0, r = m, ret = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (ha[mid] <= x) {
			ret = mid;
			l = mid + 1;
		} else r = mid - 1;
	}
	return ret;
}

void work() {
	m = ha.size();
	tree.build(1, m, 1);
	memset(dp, 0, sizeof(dp));
	int ret = 0;
	for (int i = 0; i < n; i++) {
		int idx, tmp;
		if (h[i] > ha[0]) {
			idx = Bin(h[i] - 1) + 1;
			tmp = tree.query(1, idx, 1);
			dp[i] = tmp + g[i];
		} else {
			dp[i] = g[i];
		}
		idx = Bin(h[i]) + 1;
		tree.update(idx, dp[i], 1);
		ret = max(ret, dp[i]);
	}
	printf("%d\n", ret);
}

int main() {
	freopen("in.txt", "r", stdin);
	while (~scanf("%d", &n)) {
		ha.clear();
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &h[i], &g[i]);
			ha.push_back(h[i]);
		}
		sort(ha.begin(), ha.end());
		ha.resize(unique(ha.begin(), ha.end()) - ha.begin());
		work();
	}
	return 0;
}
