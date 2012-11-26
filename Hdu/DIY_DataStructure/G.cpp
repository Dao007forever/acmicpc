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
struct Point {
	int x, y;
	void input() {
		scanf("%d%d", &x, &y);
	}
};
struct disjoint_set {
	int p[MAXN], num[MAXN], miny[MAXN], maxy[MAXN];

	void init(int n, const Point *pt) {
		for (int i = 0; i < n; i++) {
			p[i] = i; num[i] = 1;
			miny[i] = maxy[i] = pt[i].y;
		}
	}

	int find(int x) {
		return p[x] == x ? x : (p[x] = find(p[x]));
	}

	void merge(int a, int b) {
		int x = find(a), y = find(b);
		num[y] += num[x];
		if (miny[x] < miny[y])
			miny[y] = miny[x];
		if (maxy[x] > maxy[y])
			maxy[y] = maxy[x];
		p[x] = y;
	}
};
struct segment_tree {
	struct node {
		int l, r, cnt, num;
	}T[MAXN << 3];

	int lson(int rt) {
		return rt << 1;
	}

	int rson(int rt) {
		return rt << 1 | 1;
	}

	void build(int l, int r, int rt) {
		T[rt].l = l; T[rt].r = r; T[rt].cnt = T[rt].num = 0;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(l, mid, lson(rt));
		build(mid + 1, r, rson(rt));
	}

	void update(int L, int R, int val, int s, int rt) {
		if (L == T[rt].l && T[rt].r == R) {
			T[rt].cnt += s;
			T[rt].num += val * s;
			return;
		}
		int mid = (T[rt].l + T[rt].r) >> 1;
		if (R <= mid) {
			update(L, R, val, s, lson(rt));
		} else if (L > mid) {
			update(L, R, val, s, rson(rt));
		} else {
			update(L, mid, val, s, lson(rt));
			update(mid + 1, R, val, s, rson(rt));
		}
		//pushUp(rt);
	}

	pair<int, int> query(int p) {
		pair<int, int> ret(0, 0);
		int rt = 1;
		while (1) {
			ret.first += T[rt].cnt;
			ret.second += T[rt].num;
			if (T[rt].l == T[rt].r) break;
			int mid = (T[rt].l + T[rt].r) >> 1;
			if (p <= mid) rt = lson(rt);
			else rt = rson(rt);
		}
		return ret;
	}
};

int n, m;
Point ps[MAXN];
disjoint_set ds;
segment_tree st;
vector<int> v;

void pre() {
	v.clear();
	for (int i = 0; i < n; i++)
		v.PB(ps[i].y);
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for (int i = 0; i < n; i++)
		ps[i].y = lower_bound(v.begin(), v.end(), ps[i].y) - v.begin();
	st.build(0, v.size() * 2, 1);
	for (int i = 0; i < n; i++)
		st.update(ps[i].y * 2, ps[i].y * 2, 1, 1, 1);
}

void make(int a, int b) {
	int x = ds.find(a), y = ds.find(b);
	if (x == y) return;
	st.update(ds.miny[x] * 2, ds.maxy[x] * 2, ds.num[x], -1, 1);
	st.update(ds.miny[y] * 2, ds.maxy[y] * 2, ds.num[y], -1, 1);
	ds.merge(a, b);
	int k = ds.find(a);
	st.update(ds.miny[k] * 2, ds.maxy[k] * 2, ds.num[k], 1, 1);
}

int main() {
	freopen("G.in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			ps[i].input();
		pre();
		ds.init(n, ps);
		scanf("%d", &m);
		while (m--) {
			char op[11];
			scanf("%s", op);
			if (*op == 'r') {
				int a, b;
				scanf("%d%d", &a, &b);
				make(a, b);
			} else {
				double c;
				scanf("%lf", &c);
				int p = upper_bound(v.begin(), v.end(), (int)c) - v.begin();
				if (p == 0) {
					printf("0 0\n");
					continue;
				}
				pair<int, int> ret = st.query(p * 2 - 1);
				printf("%d %d\n", ret.first, ret.second);
			}
		}
	}
	return 0;
}
