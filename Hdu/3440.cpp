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
/*------------#include omitted-----------*/

#define MAXN 100005
const int inf = 1 << 30;
struct Graph {
	int n;
	int dis[MAXN];
	bool vst[MAXN];
	vector<pair<int, int> > adj[MAXN];

	void init(int n) {
		this->n = n;
		for (int i = 0; i <= n; i++)
			adj[i].clear();
	}

	void addEdge(int u, int v, int w) {
		adj[u].PB(MP(v, w));
	}

	int que[MAXN];
	int spfa(int st, int ed) {
		memset(vst, 0, sizeof(vst));
		for (int i = 0; i <= n; i++)
			dis[i] = inf;
		int head = 0, tail = 0;
		que[tail++] = st;
		dis[st] = 0;
		vst[st] = true;
		while (head != tail) {
			int u = que[head];
			head = (head + 1) % MAXN;
			vst[u] = false;
			for (int i = 0; i < adj[u].size(); i++) {
				int v = adj[u][i].first, tmp = dis[u] + adj[u][i].second;
				if (dis[v] > tmp) {
					dis[v] = tmp;
					if (!vst[v]) {
						vst[v] = true;
						que[tail] = v;
						tail = (tail + 1) % MAXN;
					}
				}
			}
		}
		return dis[ed];
	}
}g;

int n, d;
struct House {
	int h, id;
}p[MAXN];

bool cmp(House a, House b) {
	return a.h < b.h;
}

bool ok() {
	for (int i = 1; i <= n - 1; i++)
		if (abs(p[i].id - p[i + 1].id) > d) return false;
	return true;
}

void work() {
	scanf("%d%d", &n, &d);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &p[i].h);
		p[i].id = i;
	}
	sort(p + 1, p + n + 1, cmp);
	if (!ok()) {
		printf("-1\n");
		return;
	}
	g.init(n);
	for (int i = 1; i <= n - 1; i++) {
		int x = min(p[i].id, p[i + 1].id);
		int y = max(p[i].id, p[i + 1].id);
		g.addEdge(x, y, d);
		g.addEdge(i + 1, i, -1);
	}
	int st = min(p[1].id, p[n].id);
	int ed = max(p[1].id, p[n].id);
	int ret = g.spfa(st, ed);
	printf("%d\n", ret);
}

int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case %d: ", cas);
		work();
	}
	return 0;
}
