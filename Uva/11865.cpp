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

#define maxV 105
#define maxE 200005
typedef long long F;
const F inf = 1ll<<60;
struct Edge {
    int u, v;
    F cost;
};
int ans_root;
struct DirectedMST {
    int V, E;
    Edge edge[maxE];
    int pre[maxV], ID[maxV], vis[maxV];
    F In[maxV];

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
            //1.找最小入边
            for (int i = 0; i < V; i++) In[i] = inf;
            for (int i = 0; i < E; i++) {
                int u = edge[i].u, v = edge[i].v;
                if (edge[i].cost < In[v] && u != v) {
                    pre[v] = u;
                    In[v] = edge[i].cost;
                    /*下面两句用来求虚根，ans_root减去原图中的边数就是原图中的根，这里不能用edge[i].v作为
                     *ans_root，因为edge[i]里的内容是会变化的，而新增的m~m+n-1则是虚边，而第i条虚边到达的
                     *点就是在新图中虚根到达的点，也即原图中的根
                     */
                    /*if (u == root) {
                        ans_root = i;
                    }*/
                }
            }
            for (int i = 0; i < V; i++) {
                if (i == root) continue;
                if (In[i] == inf) return -1;//除了根意外有点没有入边，则根无法到达它
            }
            //2.找环
            int cntnode = 0;
            memset(ID, -1, sizeof(ID));
            memset(vis, -1, sizeof(vis));
            In[root] = 0;
            for (int i = 0; i < V; i++) {//标记每个环
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
            if (cntnode == 0) break;//无环
            for (int i = 0; i < V; i++) if (ID[i] == -1) {
                ID[i] = cntnode++;
            }
            //3.缩点，重新标记
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
};

struct edge {
	int u, v, b, c;
	edge() {}
	edge(int u, int v, int b, int c) : u(u), v(v), b(b), c(c) {}
};
vector<edge> es;
int n, m, C;
vector<int> graph[maxV];
bool vis[maxV];

void dfs(int u) {
	vis[u] = true;
	for (int i = 0, v; i < graph[u].size(); i++) {
		if (!vis[v = graph[u][i]]) {
			dfs(v);
		}
	}
}

bool check(int lim) {
	DirectedMST dmst;
	dmst.init(n);
	for (int i = 0; i < n; i++) graph[i].clear();
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < m; i++) {
		int u = es[i].u, v = es[i].v, b = es[i].b, c = es[i].c;
		if (b >= lim) {
			graph[u].PB(v);
			dmst.addEdge(u, v, c);
		}
	}
	dfs(0);
	for (int i = 0; i < n; i++)
		if (!vis[i]) return false;
	int cost = dmst.solve(0);
	return cost <= C;
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		es.clear();
		scanf("%d%d%d", &n, &m, &C);
		for (int i = 0; i < m; i++) {
			int u, v, b, c;
			scanf("%d%d%d%d", &u, &v, &b, &c);
			es.PB(edge(u, v, b, c));
		}
		int lo = 0, hi = 1000000, ret = -1;
		while (lo <= hi) {
			int mid = (lo + hi) >> 1;
			if (check(mid)) {
				ret = mid;
				lo = mid + 1;
			} else hi = mid - 1;
		}
		if (ret == -1) puts("streaming not possible.");
		else printf("%d kbps\n", ret);
	}
	return 0;
}