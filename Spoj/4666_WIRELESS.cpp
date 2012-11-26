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

const int MAXM = 30005;
int N, M, K;
struct Station {
	int x, y, r, b;
}s[1005];
struct Node {
	int l, r, Max, sum, add;
}T[MAXM << 2];
LL ret, ans;

inline int lson(int rt) {
	return rt << 1;
}

inline int rson(int rt) {
	return rt << 1 | 1;
}

void pushUp(int rt) {
	T[rt].Max = T[lson(rt)].Max; T[rt].sum = T[lson(rt)].sum;
	if (T[rson(rt)].Max > T[rt].Max) {
		T[rt].Max = T[rson(rt)].Max;
		T[rt].sum = T[rson(rt)].sum;
	} else if (T[rson(rt)].Max == T[rt].Max) {
		T[rt].sum += T[rson(rt)].sum;
	}
}

void pushDown(int rt) {
	if (T[rt].add) {
		T[lson(rt)].add += T[rt].add;
		T[rson(rt)].add += T[rt].add;
		T[lson(rt)].Max += T[rt].add;
		T[rson(rt)].Max += T[rt].add;
		T[rt].add = 0;
	}
}

void build(int l, int r, int rt) {
	T[rt].l = l; T[rt].r = r;
	T[rt].sum = r - l + 1;
	T[rt].Max = T[rt].add = 0;
	if (l == r) {
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
}

void update(int L, int R, int c, int rt) {
	if (L <= T[rt].l && T[rt].r <= R) {
		T[rt].add += c;
		T[rt].Max += c;
		return;
	}
	pushDown(rt);
	int mid = (T[rt].l + T[rt].r) >> 1;
	if (L <= mid) update(L, R, c, lson(rt));
	if (R > mid) update(L, R, c, rson(rt));
	pushUp(rt);
}

void solve(int x) {
	build(1, M, 1);
	for (int i = 0; i < K; i++) {
		int dx = abs(x - s[i].x);
		if (dx > s[i].r) continue;
		int delta = (int)(sqrt(s[i].r * s[i].r - dx * dx) + 1e-8);
		int l = max(1, s[i].y - delta);
		int r = min(M, s[i].y + delta);
		update(l, r, s[i].b, 1);
	}
	if (T[1].Max > ret) {
		ret = T[1].Max;
		ans = T[1].sum;
	} else if (T[1].Max == ret) {
		ans += T[1].sum;
	}
}

int main() {
	freopen("in", "r", stdin);
	while (scanf("%d", &M) != EOF) {
		scanf("%d", &N);
		scanf("%d", &K);
		ret = ans = 0;
		for (int i = 0; i < K; i++)
			scanf("%d%d%d%d", &s[i].x, &s[i].y, &s[i].r, &s[i].b);

		for (int i = 1; i <= N; i++) {
			solve(i);
		}
		cout << ret << endl;
		cout << ans << endl;
	}
	return 0;
}
