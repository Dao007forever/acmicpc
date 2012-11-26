/*
 * Author: Yang Zhang
 * Created Time: Mon 17 Sep 2012 04:01:28 PM CST
 * File Name: 12056_FZ10B.cpp
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
#define MAXN 305
const int inf = 0x7f7f7f7f;
struct Stoer_Wagner {
	int n;
	int g[MAXN][MAXN];

	void init(int n) {
		this->n = n;
		memset(g, 0, sizeof(g));
	}

	void addEdge(int i, int j, int val) {
		g[i][j] += val;
		g[j][i] += val;
	}

	int solve() {
		static bool vis[MAXN];
		static int addr[MAXN];
		static int d[MAXN];

		int ans = inf, now, pre;

		for (int i = 0; i < n; i++)
			addr[i] = i;
		while (n > 1) {
			memset(vis, 0, sizeof(vis));
			memset(d, 0, sizeof(d));
			now = 0;
			for (int i = 0; i < n - 1; i++) {
				vis[addr[now]] = true;
				pre = now;
				now = 0;
				for (int j = 0; j < n; j++) {
					if (vis[addr[j]]) continue;
					d[j] += g[addr[pre]][addr[j]];
					if (d[j] > d[now]) now = j;
				}
			}
			ans = min(ans, d[now]);
			for (int i = 0; i < n; i++)
				g[addr[i]][addr[pre]] = (g[addr[pre]][addr[i]] += g[addr[now]][addr[i]]);
			addr[now] = addr[--n];
		}
		return ans;
	}
}mc;

int main() {
	int n, m, s;
	while (~scanf("%d%d%d", &n, &m, &s)) {
		if (n == 0 && m == 0 && s == 0) break;
		mc.init(n);
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			mc.addEdge(a, b, c);
		}
		printf("%d\n", mc.solve());
	}
	return 0;
}

