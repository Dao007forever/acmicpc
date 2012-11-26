#define MAXN 50005
const int inf = 0x3f3f3f3f;
struct OriQuery {
	int u, v, ans;
}query[MAXN];
struct Edge {
	int v, w, next;
};
struct Query {
	int v, id, next;
};
struct Tarjan_LCA {
	int n;
	int Max[MAXN], Min[MAXN], up[MAXN], dw[MAXN], p[MAXN];
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
			up[x] = max(Max[px] - Min[x], max(up[x], up[px]));
			dw[x] = max(Max[x] - Min[px], max(dw[x], dw[px]));
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
			}
		}
		for (int i = rHead[u]; i != -1; i = redge[i].next) {
			int idx = redge[i].v;
			int u = query[idx].u, v = query[idx].v;
			find(u); find(v);
			query[idx].ans = max(Max[v] - Min[u], max(up[u], dw[v]));
		}
	}
}g;

//Poj3728
int n, Q;
int val[MAXN];
int main() {
	while (~scanf("%d", &n)) {
		g.init(n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &val[i]);
		for (int i = 1; i <= n; i++)
			g.Max[i] = g.Min[i] = val[i];
		for (int i = 1; i < n; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			g.addEdge(a, b, 0);
			g.addEdge(b, a, 0);
		}
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			query[i].u = a; query[i].v = b;
			g.addQuery(a, b, i);
			g.addQuery(b, a, i);
		}
		g.dfs(1);
		for (int i = 0; i < Q; i++)
			printf("%d\n", query[i].ans);
	}
	return 0;
}