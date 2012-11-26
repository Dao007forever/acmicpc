/*
 * Author: Yang Zhang
 * Created Time: Wed 29 Aug 2012 03:30:29 PM CST
 * File Name: 219E.cpp
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

#define MAXN 200005
struct SegTree {
	struct Node {
		int l, r, maxlen, len, sl, sr;
	}T[MAXN << 2];

	int lson(int rt) {return rt << 1; }
	int rson(int rt) {return rt << 1 | 1; }
	void pushUp(int rt) {
		T[rt].maxlen = max(T[lson(rt)].maxlen, T[rson(rt)].maxlen);
		T[rt].maxlen = max(T[rt].maxlen, T[lson(rt)].sr + T[rson(rt)].sl);
		T[rt].sl = T[lson(rt)].sl;
		if (T[lson(rt)].sl == T[lson(rt)].len) {
			T[rt].sl += T[rson(rt)].sl;
		}
		T[rt].sr = T[rson(rt)].sr;
		if (T[rson(rt)].sr == T[rson(rt)].len) {
			T[rt].sr += T[lson(rt)].sr;
		}
		T[rt].len = T[lson(rt)].len + T[rson(rt)].len;
	}
	void build(int l, int r, int rt) {
		T[rt].l = l; T[rt].r = r;
		T[rt].maxlen = T[rt].sl = T[rt].sr = T[rt].len = r - l + 1;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(l, mid, lson(rt));
		build(mid + 1, r, rson(rt));
	}
	void update(int pos, int delta, int rt) {
		if (T[rt].l == T[rt].r) {
			if (delta == 1) {
				T[rt].maxlen = T[rt].sl = T[rt].sr = 0;
			} else {
				T[rt].maxlen = T[rt].sl = T[rt].sr = 1;
			}
			return;
		}
		int mid = (T[rt].l + T[rt].r) >> 1;
		if (pos <= mid) update(pos, delta, lson(rt));
		else update(pos, delta, rson(rt));
		pushUp(rt);
	}
	int query(int tar, int rt) {
		if (T[rt].l == T[rt].r) return T[rt].l;
		if (T[rt].l == 1 && T[rt].sl >= tar) return 1;
		int mid = (T[rt].l + T[rt].r) >> 1;
		if (T[lson(rt)].maxlen + 1 >= 2 * tar) {
			return query(tar, lson(rt));
		}
		if (T[lson(rt)].sr + T[rson(rt)].sl + 1 >= 2 * tar) {
			return mid - T[lson(rt)].sr + tar;
		}
		return query(tar, rson(rt));
	}
	
}tree;

int n, m;
map<int, int> posid;
int main() {
	cin >> n >> m;
	tree.build(1, n, 1);
	for (; m--; ) {
		int t, id;
		cin >> t >> id;
		if (t == 1) {
			int len = (tree.T[1].maxlen + 1) / 2;
			len = max(len, tree.T[1].sl);
			len = max(len, tree.T[1].sr);

			int pos = tree.query(len, 1);
			posid[id] = pos;
			tree.update(pos, 1, 1);
			printf("%d\n", pos);
		} else {
			int pos = posid[id];
			tree.update(pos, -1, 1);
		}
	}
	return 0;
}

