/*
 * SPFA
 */
struct Edge {
	int v, next, w;
};
struct Graph {

	int N, M;
	Edge edge[maxm * 2];
	int num, Head[maxn];
	int dis[maxn], vis[maxn];

	Graph() {}

	void init(int N, int M) {
		this->N = N;
		this->M = M;
		num = 0;
		memset(Head, -1, sizeof(Head));
	}

	void addEdge(int u, int v, int w) {
		edge[num].v = v;
		edge[num].w = w;
		edge[num].next = Head[u];
		Head[u] = num++;
	}

	int SPFA(int st, int ed) {
		for (int i = 1; i <= N; i++) {
			dis[i] = inf;
			vis[i] = false;
		}
		vis[st] = true;
		dis[st] = 0;
		queue<int> Q;
		Q.push(st);
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			vis[u] = false;
			for (int i = Head[u]; i != -1; i = edge[i].next) {
				int v = edge[i].v;
				if (dis[u] + edge[i].w < dis[v]) {
					dis[v] = dis[u] + edge[i].w;
					if (!vis[v]) {
						vis[v] = true;
						Q.push(v);
					}
				}
			}
		}
		return dis[ed];
	}
};
