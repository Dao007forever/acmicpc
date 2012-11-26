#define MAXN 100005
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
}g;

//Spoj3978 Distance Query
int n, Q;
int main() {
	while (~scanf("%d", &n)) {
		g.init(n);
		for (int i = 1; i < n; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			g.addEdge(u, v, w);
			g.addEdge(v, u, w);
		}
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%d%d", &query[i].u, &query[i].v);
			g.addQuery(query[i].u, query[i].v, i);
			g.addQuery(query[i].v, query[i].u, i);
		}
		g.dfs(1);
		for (int i = 0; i < Q; i++) {
			printf("%d %d\n", query[i].Min, query[i].Max);
		}
	}
	return 0;
}