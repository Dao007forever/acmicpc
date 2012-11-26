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
#define th(x) this->x = x
const int MAXN = 1500 + 10;
const int MAXM = 30000 + 10;
const int inf = 0x3f3f3f3f;
struct Nod
{
        int b, next;
        int cap, flow;
        void init(int b, int cap, int next)
        {
                th(b);
                th(cap);
                th(next);
        }
};
struct SAP
{
        int E[MAXN], n;
        int h[MAXN], vh[MAXN], source, sink;
        Nod buf[MAXM * 4]; int len;
        void init(int n)
        {
                this->n = n;
                len = 0;
                memset(E, 255, sizeof(E));
        }
        void addCap(int i, int j, int cap1, int cap2 = 0)
        {
                buf[len].init(j, cap1, E[i]);
                E[i] = len++;
                buf[len].init(i, cap2, E[j]);
                E[j] = len++;
        }
        int sap(const int idx, const int maxCap)
        {
                if (idx == sink)
                        return maxCap;
                int l = maxCap, d, minH = n;
                for (int i = E[idx]; i != -1; i = buf[i].next)
                {
                        Nod & nod = buf[i];
                        if (nod.cap-nod.flow > 0)
                        {
                                if (h[idx] == h[nod.b] + 1)
                                {
                                        d = sap(nod.b, min(l, nod.cap - nod.flow));
                                        nod.flow += d;
                                        buf[i ^ 1].flow -= d;
                                        l -= d;
                                        if (h[source] == n || l == 0) return maxCap - l;
                                }
                                minH = min(minH, h[nod.b] + 1);
                        }
                }
                if (l == maxCap)
                {
                        vh[h[idx]]--;
                        vh[minH]++;
                        if (vh[h[idx]] == 0)
                                h[source] = n;
                        h[idx] = minH;
                }
                return maxCap - l;
        }
        int solve(int source, int sink)
        {
                if (source == sink) return inf;
                th(source); th(sink);
                memset(h, 0, sizeof(h));
                memset(vh, 0, sizeof(vh));
                for (int i = 0; i < len; i++)
                        buf[i].flow = 0;
                int ans = 0;
                while (h[source] != n)
                        ans += sap(source, inf);
                return ans;
        }
}sap;
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

	void addEdge(int a, int b, int c) {
		adj[a].PB(MP(b, c));
	}

	void dijkstra(int st) {
		for (int i = 1; i <= n; i++)
			dis[i] = inf, vst[i] = false;
		dis[st] = 0;
		priority_queue<pair<int, int> > Q;
		Q.push(MP(0, st));
		while (!Q.empty()) {
			pair<int, int> cur = Q.top(); Q.pop();
			int u = cur.second;
			vst[u] = true;
			for (int i = 0; i < adj[u].size(); i++) {
				int v = adj[u][i].first, w = adj[u][i].second;
				if (!vst[v] && dis[u] + w < dis[v]) {
					dis[v] = dis[u] + w;
					Q.push(MP(-dis[v], v));
				}
			}
		}
	}

	void build() {
		dijkstra(1);
		sap.init(n + 1);
		for (int i = 1; i <= n; i++)
			for (int j = 0; j < adj[i].size(); j++) {
				int v = adj[i][j].first, w = adj[i][j].second;
				if (dis[i] + w == dis[v]) {
					sap.addCap(i, v, 1);
				}
			}
	}	

	void work() {
		if (dis[n] == inf || n == 1) {
			printf("0\n");
			return;
		}
		int ret = sap.solve(1, n);
		printf("%d\n", ret);
	}
}g;

int main() {
	int Test, n;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		g.init(n);
		int a, b, c;
		while (scanf("%d%d%d", &a, &b, &c) && a + b + c) {
			g.addEdge(a, b, c);
			g.addEdge(b, a, c);
		}
		g.build();
		g.work();
	}
	return 0;
}
