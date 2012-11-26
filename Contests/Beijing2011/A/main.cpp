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

#define MAXN 1005
const double inf = 1e20;
struct OriQuery {
	int u, v;
	double Max, Min;
}query[1000005];
struct Edge {
	int v, w, next;
};
struct Query {
	int v, id, next;
};
struct Tarjan_LCA {
	int n;
	double Max[MAXN], Min[MAXN];
	int p[MAXN];
	bool vst[MAXN];
	int edgenum, qedgenum, retnum;
	Edge edge[1000005], redge[1000005];
	int Head[MAXN], rHead[MAXN];
	Query qedge[1000005];
	int qHead[MAXN];

	void init(int n) {
		this->n = n;
		edgenum = qedgenum = retnum = 0;
		memset(Head, -1, sizeof(Head));
		memset(qHead, -1, sizeof(qHead));
		memset(rHead, -1, sizeof(rHead));
		for (int i = 0; i <= n; i++) {
			p[i] = i;
			vst[i] = false;
			Max[i] = -inf;
			Min[i] = inf;
		}
	}

	void addEdge(int u, int v, double w) {
		//cout << u << " " << v << " " << w << endl;
		edge[edgenum].v = v;
		edge[edgenum].w = w;
		edge[edgenum].next = Head[u];
		Head[u] = edgenum++;
	}

	void addQuery(int u, int v, int id) {
		qedge[qedgenum].v = v;
		qedge[qedgenum].id = id;
		qedge[qedgenum].next = qHead[u];
		qHead[u] = qedgenum++;
	}

	void addRet(int u, int v, double w) {
		redge[retnum].v = v;
		redge[retnum].w = w;
		redge[retnum].next = rHead[u];
		rHead[u] = retnum++;
	}

	int find(int x) {
		if (x != p[x]) {
			int px = p[x];
			p[x] = find(p[x]);
			Max[x] = max(Max[x], Max[px]);
			Min[x] = min(Min[x], Min[px]);
		}
		return p[x];
	}

	void dfs(int u) {
		vst[u] = true;
		for (int i = qHead[u]; i != -1; i = qedge[i].next) {
			int v = qedge[i].v;
			if (vst[v]) {
				int pv = find(v);
				addRet(pv, qedge[i].id, 0);
			}
		}
		for (int i = Head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].v;
			if (!vst[v]) {
				dfs(v);
				p[v] = u;
				Max[v] = Min[v] = edge[i].w;
			}
		}
		for (int i = rHead[u]; i != -1; i = redge[i].next) {
			int idx = redge[i].v;
			int u = query[idx].u, v = query[idx].v;
			find(u); find(v);
			query[idx].Max = max(Max[u], Max[v]);
			query[idx].Min = min(Min[u], Min[v]);
		}
	}
}g;
struct DisJointSet{
	int rank[MAXN], parent[MAXN];

	void init(int n) {
		for (int i = 0; i < n; i++) {
			rank[i] = 0;
			parent[i] = i;
		} 
	}

	int Find(int x) {
		if (parent[x] == x) return x;
		return parent[x] = Find(parent[x]);
	}

	void Union(int x, int y) {
		x = Find(x);
		y = Find(y);

		if (x == y) return;
		
		if (rank[x] >= rank[y]) {
			parent[y] = x;
			if (rank[x] == rank[y])
				rank[x]++;
		}
		else {
			parent[x] = y;
		}
	}

	int count(int n) {
		int ret = 0;
		for (int i = 0; i < n; i++)
			ret += parent[i] == i;
		return ret;
	}
}dsu;
int n;
double sum;
int x[MAXN], y[MAXN], p[MAXN];
int E, Q;
struct oriEdge {
	int u, v;
	double w;
	oriEdge() {}
	oriEdge(int u, int v, double w) : u(u), v(v), w(w) {}
	bool operator < (const oriEdge &pt) const {
		return w < pt.w;
	}
}ed[1000005];
void kruskal() {
	sort(ed, ed + E);
	sum = 0;
	dsu.init(n);
	for (int i = 0; i < E; i++) {
		int u = ed[i].u, v = ed[i].v;
		double w = ed[i].w;
		if (dsu.Find(u) != dsu.Find(v)) {
			g.addEdge(u, v, w);
			g.addEdge(v, u, w);
			sum += w;
			dsu.Union(u, v);
		}
	}
}
int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d%d%d", &x[i], &y[i], &p[i]);
		}
		g.init(n);
		E = 0; Q = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				int d = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
				ed[E] = oriEdge(i, j, sqrt(d));
				E++;
				query[Q].u = i; query[Q].v = j;
				g.addQuery(query[Q].u, query[Q].v, Q);
				g.addQuery(query[Q].v, query[Q].u, Q);
				Q++;
			}
		}
		kruskal();
		g.dfs(0);
		double ret = 0;
		for (int i = 0; i < Q; i++) {
			int u = query[i].u, v = query[i].v;
			//cout << u << " " << v << " " << query[i].Max << endl;
			int A = p[u] + p[v];
			double B = sum - query[i].Max;
			double tmp = ((double)A / B);
			if (tmp > ret) {
				ret = tmp;
			}
		}
		printf("%.2f\n", ret);
	}
	return 0;
}