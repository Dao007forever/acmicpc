/*
 * Author: Yang Zhang
 * Created Time: Sat 01 Sep 2012 10:58:23 PM CST
 * File Name: 412_COVER.cpp
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

#define MAXN 10005
#define MAXM 1000005
struct node {
	int w, id;
	bool operator < (const node *t) const {
		return w < t.w;
	}
}p[MAXN];
int to[MAXM], prev[MAXM];
int E, last[MAXN], id[MAXN], lx[MAXN], ly[MAXN], fa[MAXN], vis[MAXN];

void addEdge(int u, int v) {
	to[E] = v; prev[E] = last[u]; last[u] = E++;
}

void init() {
	E = 0;
	memset(last, -1, sizeof(last));
	memset(vis, 0, sizeof(vis));
	memset(lx, 0, sizeof(lx));
	memset(ly, 0, sizeof(ly));
}

int main() {
	int Test;
	scanf("%d", &Test);
	for (; Test--; ) {
		init();
		scanf("%d%d%d", &k, &n, &m);
		for (int i = 1; i <= n; i++) scanf("%d", &p[i].w), p[i].id = i;
		sort(p + 1, p + n + 1);
		for (int i = 1; i <= n; i++) id[p[i].id] = i;
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			addEdge(id[a], id[b]);
		}
		bool flag = true;
		ret = 0;
		for (int i = 1; i <= k; i++)
			if (!find()) {
				flag = false;
				break;
			}
		if (!flag) puts("NONE");
		else printf("%d\n", ret);
	}
	return 0;
}

