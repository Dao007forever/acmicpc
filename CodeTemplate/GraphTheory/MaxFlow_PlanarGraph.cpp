//#pragma comment(linker, "/STACK:16777216") (if STACK OverFlow)
//MaxFlow for Planar Graph
const double eps =1e-8;
const double pi = acos(-1.0);
int sig(double d) {
	return (d > eps) - (d < -eps);
}
const int MAXN = 100005;
const int MAXE = 2000005;
const int maxV = 300005;
const double inf = 1e20;
struct Edge {
	int in, out; double angle;
	Edge() {}
	Edge (int _in, int _out, double _angle) {
		in = _in; out = _out; angle = _angle;
	}
	bool operator < (const Edge &p) const {
		return sig(angle - p.angle) < 0;
	}
};
struct Graph {
	int n, E;
	double dis[maxV];
	bool vis[maxV];
	int to[MAXE], prev[MAXE], last[maxV];
	double len[MAXE];

	void init(int n) {
		this->n = n;
		E = 0;
		memset(last, -1, sizeof(last));
	}

	void addEdge(int u, int v, double w) {
		//printf("%d %d %.3f\n", u, v, w);
		to[E] = v; len[E] = w; prev[E] = last[u]; last[u] = E++;
	}

	priority_queue<pair<double, int> > q;
	double dijkstra(int st, int ed) {
		for (int i = 0; i < n; i++)
			dis[i] = inf, vis[i] = false;
		dis[st] = 0;
		q.push(MP(0.0, st));
		while (!q.empty()) {
			int u = q.top().second; q.pop();
			vis[u] = true;
			for (int i = last[u]; ~i; i = prev[i]) {
				int v = to[i];
				if (!vis[v] && sig(dis[v] - (dis[u] + len[i])) > 0) {
					dis[v] = dis[u] + len[i];
					q.push(MP(-dis[v], v));
				}
			}
		}
		return dis[ed];
	}
}g;

int nxt[MAXE], belong[MAXE];
bool vis[MAXE];
int source, sink, cnt;
double tx[MAXN], ty[MAXN], Cap[MAXN];
vector<Edge> vertex[MAXN];

int edge1(int x) { 
	return x << 1;
}
int edge2(int x) {
	return (x << 1) | 1;
}

void dfs(int x, int ori) {
	if (nxt[x] != ori) dfs(nxt[x], ori);
	belong[x] = cnt, vis[x] = true;
}

//Hdu 4180
int main() {
	int Test;
	scanf("%d", &Test);
	int n, m;
	while (Test--) {
		scanf("%d%d", &n, &m);
		memset(belong, 0, sizeof(belong));
		memset(nxt, 0, sizeof(nxt));
		source = sink = 0;
		for (int i = 0; i < n; i++) vertex[i].clear();
		for (int i = 0; i < n; i++) {
			scanf("%lf%lf", &tx[i], &ty[i]);
			if (sig(tx[source] - tx[i]) > 0) source = i;
			if (sig(tx[sink] - tx[i]) < 0) sink = i;
		}

		for (int i = 0; i < m; i++) {
			int a, b; double x;
			scanf("%d%d%lf", &a, &b, &x);
			a--; b--;
			if (a == b) {
				--m; --i;
				continue;
			}
			int eg1 = edge1(i), eg2 = edge2(i);
			Cap[i] = x;
			double anga = atan2(ty[b] - ty[a], tx[b] - tx[a]);
			double angb = atan2(ty[a] - ty[b], tx[a] - tx[b]);
			vertex[a].PB(Edge(eg1, eg2, anga));
			vertex[b].PB(Edge(eg2, eg1, angb));
		}
		int addr1 = edge1(m), addr2 = edge2(m);
		vertex[source].PB(Edge(addr1, addr2, -pi));
		vertex[sink].PB(Edge(addr2, addr1, 0));

		for (int i = 0; i < n; i++) {
			sort(vertex[i].begin(), vertex[i].end());
			int sz = vertex[i].size();
			for (int j = 0; j < sz - 1; j++)
				nxt[vertex[i][j].in] = vertex[i][j + 1].out;
			if (sz == 0) continue;
			nxt[vertex[i][sz - 1].in] = vertex[i][0].out;
		}

		cnt = 0;
		memset(vis, 0, sizeof(vis));
		for (int i = 0; i <= addr2; i++)
			if (!vis[i]) dfs(i, i), cnt++;
		g.init(cnt);
		for (int i = 0; i < m; i++) {
			int eg1 = edge1(i), eg2 = edge2(i);
			g.addEdge(belong[eg1], belong[eg2], Cap[i]);
			g.addEdge(belong[eg2], belong[eg1], Cap[i]);
		}
		double ret = g.dijkstra(belong[addr1], belong[addr2]);
		printf("%.0f\n", ret);
	}
	return 0;
}

