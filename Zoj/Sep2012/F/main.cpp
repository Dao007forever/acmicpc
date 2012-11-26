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

#define MAXN 50005
struct DisJointSet{
	LL rank[MAXN], parent[MAXN];

	void init(LL n) {
		for (LL i = 0; i <= n; i++) {
			rank[i] = 0;
			parent[i] = i;
		} 
	}

	LL Find(LL x) {
		if (parent[x] == x) return x;
		return parent[x] = Find(parent[x]);
	}

	void Union(LL x, LL y) {
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

	LL count(LL n) {
		LL ret = 0;
		for (LL i = 0; i < n; i++)
			ret += parent[i] == i;
		return ret;
	}
}dsu;
struct OriQuery {
	LL u, v;
	LL ans;
}query[MAXN];
struct Edge {
	LL v, w, next;
};
struct Query {
	LL v, id, next;
};
struct Tarjan_LCA {
	LL n;
	LL Max[MAXN], Min[MAXN], up[MAXN], dw[MAXN], p[MAXN];
	bool vst[MAXN];
	LL edgenum, qedgenum, retnum;
	Edge edge[MAXN << 3], redge[MAXN << 3];
	LL Head[MAXN], rHead[MAXN];
	Query qedge[MAXN << 3];
	LL qHead[MAXN];

	void init(LL n) {
		this->n = n;
		edgenum = qedgenum = retnum = 0;
		memset(Head, -1, sizeof(Head));
		memset(qHead, -1, sizeof(qHead));
		memset(rHead, -1, sizeof(rHead));
		memset(up, 0, sizeof(up));
		memset(dw, 0, sizeof(dw));
		for (LL i = 0; i <= n; i++) {
			p[i] = i;
			vst[i] = false;
		}
	}

	void addEdge(LL u, LL v, LL w) {
		edge[edgenum].v = v;
		edge[edgenum].w = w;
		edge[edgenum].next = Head[u];
		Head[u] = edgenum++;
	}

	void addQuery(LL u, LL v, LL id) {
		qedge[qedgenum].v = v;
		qedge[qedgenum].id = id;
		qedge[qedgenum].next = qHead[u];
		qHead[u] = qedgenum++;
	}

	void addRet(LL u, LL v, LL w) {
		redge[retnum].v = v;
		redge[retnum].w = w;
		redge[retnum].next = rHead[u];
		rHead[u] = retnum++;
	}

	LL find(LL x) {
		if (x != p[x]) {
			LL px = p[x];
			p[x] = find(p[x]);
			up[x] = max(Max[px] - Min[x], max(up[x], up[px]));
			dw[x] = max(Max[x] - Min[px], max(dw[x], dw[px]));
			Max[x] = max(Max[x], Max[px]);
			Min[x] = min(Min[x], Min[px]);
		}
		return p[x];
	}

	void dfs(LL u) {
		vst[u] = true;
		for (LL i = qHead[u]; i != -1; i = qedge[i].next) {
			LL v = qedge[i].v;
			if (vst[v]) {
				LL pv = find(v);
				addRet(pv, qedge[i].id, 0);
			}
		}
		for (LL i = Head[u]; i != -1; i = edge[i].next) {
			LL v = edge[i].v;
			if (!vst[v]) {
				dfs(v);
				p[v] = u;
			}
		}
		for (LL i = rHead[u]; i != -1; i = redge[i].next) {
			LL idx = redge[i].v;
			LL u = query[idx].u, v = query[idx].v;
			find(u); find(v);
			query[idx].ans = max(Max[v] - Min[u], max(up[u], dw[v]));
		}
	}
}g;

struct oriEdge {
	LL u, v;
	LL w;
	bool operator < (const oriEdge &p) const {
		return w > p.w;
	}
}orie[MAXN];
LL n, m, Q;
LL val[MAXN];

void kruskal() {
	dsu.init(n);
	LL sum = 0;
	sort(orie, orie + m);
	for (LL i = 0; i < m; i++) {
		LL u = orie[i].u, v = orie[i].v;
		if (dsu.Find(u) != dsu.Find(v)) {
			sum += orie[i].w;
			//cout << u << " " << v << endl;
			g.addEdge(u, v, 0);
			g.addEdge(v, u, 0);
			dsu.Union(u, v);
		}
	}
	cout << sum << endl;
	//prLLf("%d\n", sum);
}

int main(int argc, char const *argv[])
{
	while (cin >> n) {
		g.init(n);
		for (LL i = 1; i <= n; i++) {
			//scanf("%d", &val[i]);
			cin >> val[i];
			g.Max[i] = g.Min[i] = val[i];
		}
		cin >> m;
		//scanf("%d", &m);
		for (LL i = 0; i < m; i++) {
			//scanf("%d%d%d", &orie[i].u, &orie[i].v, &orie[i].w);
			cin >> orie[i].u >> orie[i].v >> orie[i].w;
		}
		kruskal();
		//scanf("%d", &Q);
		cin >> Q;
		for (LL i = 1; i <= Q; i++) {
			LL a, b;
			//scanf("%d%d", &a, &b);
			cin >> a >> b;
			query[i].u = a; query[i].v = b;
			g.addQuery(a, b, i);
			g.addQuery(b, a, i);
		}
		g.dfs(1);
		for (LL i = 1; i <= Q; i++) {
			cout << max(query[i].ans, 0ll) << endl;
			//printf("%d\n", query[i].ans);
		}
	}
	return 0;
}