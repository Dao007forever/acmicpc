/*
 * Author: Yang Zhang
 * Created Time: Fri 07 Sep 2012 04:31:27 PM CST
 * File Name: 4483_MROADS.cpp
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
int n, K, E, limit, now;
int to[MAXN], c1[MAXN], c2[MAXN], prev[MAXN], last[MAXN];
int d1[MAXN], d2[MAXN];

void addEdge(int u, int v, int w, int x) {
	to[E] = v; c1[E] = w; c2[E] = x; prev[E] = last[u]; last[u] = E++;
}

void dfs(int u, int fa) {
	d1[u] = d2[u] = 0;
	for (int i = last[u], v; ~i; i = prev[i]) {
		if ((v = to[i]) != fa) {
			dfs(v, u);
			d1[u] = max(d1[u], d1[v] + c1[i]);
			d2[u] = max(d2[u], d2[v] + c2[i]);
		}
	}
}

bool check(int u, int fa, int delta) {
	if (delta + d1[u] - now > limit) return false;
	if (delta + d2[u] > limit) return false;
	if (delta + d1[u] <= limit) return true;
	for (int i = last[u], v; ~i; i = prev[i]) {
		if ((v = to[i]) != fa) {
			int tmp = min(c1[i] - c2[i], delta + d1[v] + c1[i] - limit);
			if (tmp < 0) tmp = 0;
			if (tmp > now) return false;
			now -= tmp;
			if (!check(v, u, delta + c1[i] - tmp))
				return false;
		}
	}
	return true;
}

int main() {
	while (~scanf("%d%d", &n, &K)) {
		E = 0;
		memset(last, -1, sizeof(last));
		for (int i = 1; i < n; i++) {
			int a, b, c, d;
			scanf("%d%d%d%d", &a, &b, &c, &d);
			addEdge(a, b, c, d); addEdge(b, a, c, d);
		}
		dfs(1, 0);
		int l = 0, r = d1[1] + 1, ret = -1;
		while (l <= r) {
			limit= (l + r) >> 1;
			now = K;
			if (check(1, 0, 0)) {
				r = limit - 1;
				ret = limit;
			} else l = limit + 1;
		}
		printf("%d\n", ret);
	}
	return 0;
}

