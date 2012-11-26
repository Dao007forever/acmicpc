/*
 * Author: Yang Zhang
 * Created Time: Thu 06 Sep 2012 09:23:09 PM CST
 * File Name: 1269_CNHARD.cpp
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
const int base = 36000 * 12;
int n, len;
int ang[MAXN], a[MAXN];
struct Graph {
	int n, depth, size;
	int dfn[MAXN], low[MAXN], id[MAXN];
	bool vis[MAXN];

	int to[MAXN * 8], prev[MAXN * 8], E;
	int last[MAXN];
	int top, S[MAXN];
	//vector<int> adj[MAXN];
	//stack<int> S;

	void init(int n) {
		this->n = n;
		//for (int i = 0; i <= 2 * n; i++)
		//	adj[i].clear();
		E = 0;
		memset(last, -1, sizeof(last));
		memset(dfn, -1, sizeof(dfn));
		memset(low, 0, sizeof(low));
		memset(vis, false, sizeof(vis));
		memset(id, 0, sizeof(id));
		top = 0;
		//while (!S.empty()) S.pop();
	}

	void addEdge(int a, int b) {
		to[E] = b; prev[E] = last[a]; last[a] = E++;
		//adj[a].PB(b);
	}

	void Tarjan(int u) {
		dfn[u] = low[u] = depth++;
		top++; S[top] = u;
		//S.push(u);
		vis[u] = true;
		for (int i = last[u]; i != -1; i = prev[i]) {
		//for (int i = 0; i < adj[u].size(); i++) {
		//	int v = adj[u][i];
			int v = to[i];
			if (dfn[v] == -1) {
				Tarjan(v);
				low[u] = min(low[u], low[v]);
			} else if (vis[v]) {
				low[u] = min(low[u], dfn[v]);
			}
		}
		if (low[u] == dfn[u]) {
			size++;
			int v;
			do {
				v = S[top];
				top--;
				//v = S.top();
				//S.pop();
				id[v] = size;
				vis[v] = false;
			} while (u != v);
		}
	}

	bool twosat() {
		depth = 1; size = 0;
		for (int i = 0; i < 2 * n; i++)
			if (dfn[i] == -1) Tarjan(i);
		for (int i = 0; i < n; i++)
			if (id[i] == id[i + n]) return false;
		return true;
	}

}g;

bool check(int x) {
	g.init(n);
	for (int i = 0; i < n - 1; i++)
		if (a[i + 1] - a[i] < len) {
			g.addEdge(i, i + 1 + n);
			g.addEdge(i + 1, i + n);
			g.addEdge(i + n, i + 1);
			g.addEdge(i + 1 + n, i);
		}
	if (a[n - 1] + len > base) {
		g.addEdge((n - 1) + n, n - 1);
		g.addEdge(0 + n, 0);
	}
	for (int i = x; i < n; i++)
		if (i < n - 1 || a[n - 1] + len <= base)
			g.addEdge(i + n, i);
	bool flag = g.twosat();
	return flag;
}

int main() {
	int Test;
	scanf("%d", &Test);
	for (; Test--; ) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			char name[111];
			double t;
			scanf("%s %lf", name, &t);
			ang[i] = 12 * (int)(t * 100.0 + 0.5);
		}
		scanf("%d", &len);
		len *= 100;
		if (n == 1) {
			printf("%d\n", len / 100);
			continue;
		}
		bool flag = true;
		sort(ang, ang + n);
		for (int i = 0; i < n; i++)
			if ((ang[(i+2) % n] - ang[i] + base) % base < len) {
				flag = false;
				break;
			}
		if (!flag) {
			puts("not possible");
			continue;
		}

		int ret = 1<<29;
		for (int i = 0; i < n; i++) {
			a[0] = 0;
			int k = 1;
			for (int j = i + 1; j < n; j++)
				a[k++] = ang[j] - ang[i];
			for (int j = 0; j < i; j++)
				a[k++] = (ang[j] - ang[i] + base) % base;
			int l = 0, r = n - 1, ans = -1;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (check(mid)) {
					ans = mid;
					r = mid - 1;
				} else l = mid + 1;
			}
			if (ans != -1) {
				if (ans == 0) {
					ret = min(ret, a[n - 1]);
				} else {
					ret = min(ret, a[ans - 1] + base);
				}
			}
		}
		if (ret == 1<<29) {
			puts("not possible");
		} else {
			printf("%.d\n", (ret + len) / 100);
		}
	}
	return 0;
}

