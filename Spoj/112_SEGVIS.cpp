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

struct Segment {
	int y1, y2, x;
}se[8005];
struct TNode {
	int l, r, col;
}T[8005 << 3];
vector<int> adj[8005];
int h[8005];
int n;

bool cmp(Segment a, Segment b) {
	return a.x < b.x;
}

inline int lson(int rt) {
	return rt << 1;
}

inline int rson(int rt) {
	return rt << 1 | 1;
}

inline void pushDown(int rt) {
	if (T[rt].col != -1) {
		T[lson(rt)].col = T[rson(rt)].col = T[rt].col;
		T[rt].col = -1;
	}
}

void build(int l, int r, int rt) {
	T[rt].l = l; T[rt].r = r;
	T[rt].col = -1;
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
}

void query(int L, int R, int x, int rt) {
	if (T[rt].col != -1) {
		if (h[T[rt].col] != x) {//防止重复记录
			h[T[rt].col] = x;
			adj[x].PB(T[rt].col);
		}
		return;
	}
	if (T[rt].l == T[rt].r) return;
	int mid = (T[rt].l + T[rt].r) >> 1;
	if (L <= mid) query(L, R, x, lson(rt));
	if (R > mid) query(L, R, x, rson(rt));
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

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			scanf("%d%d%d", &se[i].y1, &se[i].y2, &se[i].x);
			se[i].y1 <<= 1;
			se[i].y2 <<= 1;
			adj[i].clear();
		}

		sort(se, se + n, cmp);

		build(0, 8000 * 2, 1);
		memset(h, -1, sizeof(h));
		for (int i = 0; i < n; i++) {
			query(se[i].y1, se[i].y2, i, 1);
			update(se[i].y1, se[i].y2, i, 1);
		}
		int ret = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < SZ(adj[i]); j++) {
				int s = adj[i][j];
				for (int k1 = 0; k1 < SZ(adj[i]); k1++)
					for (int k2 = 0; k2 < SZ(adj[s]); k2++)
						if (adj[i][k1] == adj[s][k2])
							ret++;
			}
		}
		cout << ret << endl;
	}
	return 0;
}
