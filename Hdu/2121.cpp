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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

typedef long long F;
const int MAXN = 1005;
const int MAXM = MAXN * MAXN * 5;
const F inf = 1ll<<60;
struct Edge {
	int u, v;
	F cost;
};
int ans_root;
struct DirectedMST {
	int V, E;
	Edge edge[MAXM];
	int pre[MAXN], ID[MAXN], vis[MAXN];
	F In[MAXN];

	void init(int V) {
		this->V = V;
		E = 0;
	}

	void addEdge(int u, int v, F cost) {
		edge[E].u = u; edge[E].v = v; edge[E].cost = cost; E++;
	}

	F solve(int root) {
		F ret = 0;
		while (true) {
			//1.
			for (int i = 0; i < V; i++) In[i] = inf;
			for (int i = 0; i < E; i++) {
				int u = edge[i].u, v = edge[i].v;
				if (edge[i].cost < In[v] && u != v) {
					pre[v] = u;
					In[v] = edge[i].cost;
					//
					if (u == root) {
						ans_root = i;
					}
				}
			}
			for (int i = 0; i < V; i++) {
				if (i == root) continue;
				if (In[i] == inf) return -1;//
			}
			//2.
			int cntnode = 0;
			memset(ID, -1, sizeof(ID));
			memset(vis, -1, sizeof(vis));
			In[root] = 0;
			for (int i = 0; i < V; i++) {
				ret += In[i];
				int v = i;
				while (vis[v] != i && ID[v] == -1 && v != root) {
					vis[v] = i;
					v = pre[v];
				}
				if (v != root && ID[v] == -1) {
					for (int u = pre[v]; u != v; u = pre[u]) {
						ID[u] = cntnode;
					}
					ID[v] = cntnode++;
				}
			}
			if (cntnode == 0) break;//
			for (int i = 0; i < V; i++) if (ID[i] == -1) {
				ID[i] = cntnode++;
			}
			//3.
			for (int i = 0; i < E; i++) {
				int v = edge[i].v;
				edge[i].u = ID[edge[i].u];
				edge[i].v = ID[edge[i].v];
				if (edge[i].u != edge[i].v) {
					edge[i].cost -= In[v];
				}
			}
			V = cntnode;
			root = ID[root];
		}
		return ret;
	}
}dmst;

//Hdu2121
int main(int argc, char const *argv[])
{
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		LL sum = 0;
		dmst.init(n + 1);
		for (int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			u++; v++;
			dmst.addEdge(u, v, w);
			sum += w;
		}
		sum++;
		for (int i = m; i < n + m; i++) {
			dmst.addEdge(0, i - m + 1, sum);
		}
		F ans = dmst.solve(0);
		if (ans == -1 || ans - sum >= sum) puts("impossible");
		else cout << ans - sum << " " << ans_root - m << endl;
		puts("");
	}
	return 0;
}