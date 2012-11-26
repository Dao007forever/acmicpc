/*
 * Author: Yang Zhang
 * Created Time: Sun 26 Aug 2012 10:16:19 PM CST
 * File Name: 5150_JMFILTER.cpp
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

#define MAXN 1100005
int n, m, cnt;
int p[MAXN], rank[MAXN], vir[MAXN], vis[MAXN];
int find(int x) {
	if (p[x] == x) return x;
	return p[x] = find(p[x]);
}
void Union(int x, int y) {
	x = find(x); y = find(y);
	if (x == y) return;
	if (rank[x] < rank[y]) {
		rank[x] += rank[y];
		p[y] = x;
	} else {
		rank[y] += rank[x];
		p[x] = y;
	}
}
int main() {
	for (int cas = 1; scanf("%d%d", &n, &m); cas++) {
		if (n == 0 && m == 0) break;
		printf("Case #%d: ", cas);
		for (int i = 0; i < n; i++) {
			p[i] = i, rank[i] = 1, vir[i] = i;
		}
		cnt = n;
		for (; m--; ) {
			char op[5];
			scanf("%s", op);
			if (*op == 'M') {
				int a, b;
				scanf("%d%d", &a, &b);
				Union(vir[a], vir[b]);
			} else {
				int a;
				scanf("%d", &a);
				vir[a] = cnt;
				p[cnt] = cnt;
				cnt++;
			}
		}
		memset(vis, 0, sizeof(vis));
		int ret = 0;
		for (int i = 0; i < n; i++) {
			int pi = find(vir[i]);
			if (!vis[pi]) {
				ret++; vis[pi] = true;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}

