#define maxn 505
#define maxm 20005
const int inf = 0x3f3f3f3f;
struct node {
	int x, y, w;
}a[maxn], b[maxn];
int N, M;
int g[maxn][maxn], ans[maxn][maxn];

struct Nod {
	int b, nxt;
	int cap, cst;
	void init(int b, int nxt, int cap, int cst) {
		this->b = b;
		this->nxt = nxt;
		this->cap = cap;
		this->cst = cst;
	}
};
struct MinCost {
	int E[maxn]; int n;
	Nod buf[maxm * 2]; int len;
	int cnt[maxn], inq[maxn];

	int p[maxn];
	void init(int n) {
		this->n = n;
		memset(E, 255, sizeof(E));
		len = 0;
	}
	void addCap(int a, int b, int cap, int cst) {
		buf[len].init(b, E[a], cap, cst); E[a] = len++;
		//buf[len].init(a, E[b], 0, -cst); E[b] = len++;
	}
	//check negative cycle
	int spfa(int source, int sink) {
		static queue<int> q;
		static int d[maxn];
		memset(d, 63, sizeof(d));
		memset(p, 255, sizeof(p));
		memset(cnt, 0, sizeof(cnt));
		memset(inq, 0, sizeof(inq));

		//put every node into the queue!
		for (int i = 0; i < n; i++) {
			q.push(i);
		}
		int u, v;
		while (!q.empty()) {
			u = q.front(); q.pop();
			inq[u] = false;
			for (int i = E[u]; i != -1; i = buf[i].nxt) {
				v = buf[i].b;
				if (buf[i].cap > 0 && d[u] + buf[i].cst < d[v]) {
					d[v] = d[u] + buf[i].cst;
					p[v] = u;
					if (!inq[v]) {
						inq[v] = true;
						q.push(v);
						if (++cnt[v] > n) {
							return v;//find a negatice cycle
						}
					}
				}
			}
		}
		return -1;
	}
	void solve(int source, int sink) {
		int v = spfa(source, sink);
		if (v == -1) {
			printf("OPTIMAL\n");
			return;
		}
		printf("SUBOPTIMAL\n");
		//Vertex v may not be in the cycle, so we have to find a vertex in the cycle
		memset(inq, 0, sizeof(inq));
		while (!inq[v]) {
			inq[v] = true;
			v = p[v];
		}
		//augment once
		int u = v;
		do {
			if (p[u] <= N && u > N) ans[p[u]][u - N]++;
			if (p[u] > N && u <= N) ans[u][p[u] - N]--;
			u = p[u];
		} while (u != v);
		for (int i = 1; i <= N; i++) {
			printf("%d", ans[i][1]);
			for (int j = 2; j <= M; j++) {
				printf(" %d", ans[i][j]);
			}
			puts("");
		}
	}
}mc;
//Poj 2175：找一个负环，并沿这个负环增广一次，找到一个较优解
int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].w);
	for (int i = 1; i <= M; i++)
		scanf("%d%d%d", &b[i].x, &b[i].y, &b[i].w);
	mc.init(N + M + 2);
	int source = 0, sink = N + M + 1;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++) {
			g[i][j] = abs(a[i].x - b[j].x) + abs(a[i].y - b[j].y) + 1;
		}
	for (int i = 1; i <= N; i++) {
		int sum = 0;
		for (int j = 1; j <= M; j++) {
			scanf("%d", &ans[i][j]);
			sum += ans[i][j];
			mc.addCap(i, j + N, inf, g[i][j]);
			mc.addCap(j + N, i, ans[i][j], -g[i][j]);
		}
		mc.addCap(source, i, a[i].w - sum, 0);
		mc.addCap(i, source, sum, 0);
	}
	for (int i = 1; i <= M; i++) {
		int sum = 0;
		for (int j = 1; j <= N; j++) {
			sum += ans[j][i];
		}
		mc.addCap(i + N, sink, b[i].w - sum, 0);
		mc.addCap(sink, i + N, sum, 0);
	}
	mc.solve(source, sink);
	return 0;
}
