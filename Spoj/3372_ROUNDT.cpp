/*
 * Author: Yang Zhang
 * Created Time: Thu 30 Aug 2012 10:24:17 PM CST
 * File Name: 3372_ROUNDT.cpp
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

#define MAXN 2005
const int inf = 1000000000;
struct SegTree {
	struct Node {
		int l, r, sum;
	}T[MAXN << 3];
	int lson(int rt) {return rt << 1;}
	int rson(int rt) {return rt << 1 | 1;}
	void pushUp(int rt) {
		T[rt].sum = T[lson(rt)].sum + T[rson(rt)].sum;
	}
	void build(int l, int r, int rt) {
		T[rt].l = l; T[rt].r = r; T[rt].sum = 0;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(l, mid, lson(rt));
		build(mid + 1, r, rson(rt));
	}
	void update(int pos, int add, int rt) {
		if (T[rt].l == T[rt].r) {
			T[rt].sum += add;
			return;
		}
		int mid = (T[rt].l + T[rt].r) >> 1;
		if (pos <= mid) update(pos, add, lson(rt));
		else update(pos, add, rson(rt));
		pushUp(rt);
	}
	int query(int L, int R, int rt) {
		if (L <= T[rt].l && T[rt].r <= R) {
			return T[rt].sum;
		}
		int mid = (T[rt].l + T[rt].r) >> 1;
		int ret = 0;
		if (L <= mid) ret += query(L, R, lson(rt));
		if (R > mid) ret += query(L, R, rson(rt));
		return ret;
	}
}tree;

int a[MAXN], b[MAXN];
int dp[MAXN][MAXN];
int main() {
	int n;
	for (; ~scanf("%d", &n); ) {
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for (int i = 1; i <= n; i++) scanf("%d", &b[i]);
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= n; j++)
				dp[i][j] = inf;
		tree.build(1, 2 * n, 1);
		dp[0][0] = 0;
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= n; j++) {
				if (dp[i][j] == inf) continue;

				//from door No.1
				int p = a[i + 1];
				int val = tree.query(1, p, 1);
				if (i + j - val < val) val = i + j - val;
				if (dp[i][j] + val < dp[i + 1][j]) {
					dp[i + 1][j] = dp[i][j] + val;
				}

				//from door No.2
				p = b[j + 1];
				if (p > n) val = tree.query(n + 1, p, 1);
				else val = tree.query(p + 1, n, 1);
				if (i + j - val < val) val = i + j - val;
				if (dp[i][j] + val < dp[i][j + 1]) {
					dp[i][j + 1] = dp[i][j] + val;
				}
				if (j + 1 <= n) {
					tree.update(b[j + 1], 1, 1);
				}
			}
			for (int j = 1; j <= n; j++)
				tree.update(b[j], -1, 1);
			if (i + 1 <= n) {
				tree.update(a[i + 1], 1, 1);
			}
		}
		printf("%d\n", dp[n][n]);
	}
	return 0;
}

