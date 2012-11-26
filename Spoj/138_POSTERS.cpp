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

#define MAXN 40005
int n;
int l[MAXN], r[MAXN];
int h[MAXN];
map<int, int> mp;
vector<int> p;

struct TNode {
	int l, r, col;
};
struct SegTree {
	TNode T[MAXN << 2];

	int lson(int rt) {
		return rt << 1;
	}

	int rson(int rt) {
		return rt << 1 | 1;
	}

	void pushDown(int rt) {
		if (T[rt].col != -1) {
			T[lson(rt)].col = T[rson(rt)].col = T[rt].col;
			T[rt].col = -1;
		}
	}

	void build(int l, int r, int rt) {
		T[rt].l = l; T[rt].r = r; T[rt].col = -1;
		if (l == r) {
			T[rt].col = -1;
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, lson(rt));
		build(mid + 1, r, rson(rt));
	}

	void update(int L, int R, int x, int rt) {
		if (L <= T[rt].l && T[rt].r <= R) {
			T[rt].col = x;
			return;
		}
		pushDown(rt);
		int mid = (T[rt].l + T[rt].r) >> 1;
		if (L <= mid) update(L, R, x, lson(rt));
		if (R > mid) update(L, R, x, rson(rt));
	}

	void query(int L, int R, int rt) {
		if (T[rt].col != -1) {
			if (!h[T[rt].col]) {
				h[T[rt].col] = 1;
			}
			return;
		}
		if (T[rt].l == T[rt].r) return;
		int mid = (T[rt].l + T[rt].r) >> 1;
		if (L <= mid) query(L, R, lson(rt));
		if (R > mid) query(L, R, rson(rt));
	}
}st;

void output(vector<int> a) {
	for (vector<int>::iterator it = a.begin(); it != a.end(); it++)
		cout << *it << " ";
}

void solve() {
	st.build(1, 2 * n, 1);
	for (int i = 0; i < n; i++)
		st.update(l[i], r[i], i, 1);
	st.query(1, 2 * n, 1);
	int ret = 0;
	for (int i = 0; i < n; i++)
		if (h[i]) ret++;
	cout << ret << endl;
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		memset(h, 0, sizeof(h));
		p.clear();
		mp.clear();
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> l[i] >> r[i];
			p.PB(l[i]); p.PB(r[i]);
		}
		sort(p.begin(), p.end());
		p.resize(unique(p.begin(), p.end()) - p.begin());
		for (int i = 0; i < SZ(p); i++)
			mp[p[i]] = i + 1;
		for (int i = 0; i < n; i++) {
			l[i] = mp[l[i]];
			r[i] = mp[r[i]];
		}
		solve();
	}
	return 0;
}
