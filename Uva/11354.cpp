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

#define MAXN 50005
const int inf = 0x3f3f3f3f;
struct OriQuery {
	int u, v, Max, Min;
}query[MAXN];
struct Edge {
	int v, w, next;
};
struct Query {
	int v, id, next;
};
struct Tarjan_LCA {
	int n;
	int Max[MAXN], Min[MAXN], p[MAXN];
	bool vst[MAXN];
	int edgenum, qedgenum, retnum;
	Edge edge[MAXN << 3], redge[MAXN << 3];
	int Head[MAXN], rHead[MAXN];
	Query qedge[MAXN << 3];
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

	void addEdge(int u, int v, int w) {
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

	void addRet(int u, int v, int w) {
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
}tree;

struct Ed {
	int a, b, c;
	bool operator < (const Ed &pt) const {
		return c < pt.c;
	}
}es[MAXN << 1];
int p[MAXN];
int find(int x) {
	return p[x] == x ? x : p[x] = find(p[x]);
}
int main(int argc, char const *argv[])
{
	int n, m, q;
	int blank = false;
	while (~scanf("%d%d", &n, &m)) {
		if (blank) puts("");
		blank = true;
		for (int i = 1; i <= n; i++)
			p[i] = i;
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			es[i].a = a; es[i].b = b; es[i].c = c;
		}
		sort(es, es + m);
		tree.init(n);
		for (int i = 0; i < m; i++) {
			int a = es[i].a, b = es[i].b, c = es[i].c;
			int pa = find(a), pb = find(b);
			if (pa != pb) {
				//cout << a << " " << b << " " << c << endl;
				tree.addEdge(a, b, c);
				tree.addEdge(b, a, c);
				p[pa] = pb;
			}
		}
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			tree.addQuery(u, v, i);
			tree.addQuery(v, u, i);
			query[i].u = u; query[i].v = v;
		}
		tree.dfs(1);
		for (int i = 0; i < q; i++) {
			printf("%d\n", query[i].Max);
		}
	}
	return 0;
}