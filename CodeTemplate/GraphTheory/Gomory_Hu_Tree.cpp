typedef int F;
#define inf (1 << 29)
#define maxV 205
#define maxE 160005
struct Dinic {
	int V, E;
	F cap[maxE], flow[maxE];
	int to[maxE], prev[maxE];
	int level[maxV], used[maxV], last[maxV];
	bool mkS[maxV];

	void init(int n) {
		V = n; E = 0;
		for (int i = 0; i < V; i++) last[i] = -1;
	}

	void reset() {
		memset(mkS, 0, sizeof(mkS));
		memset(flow, 0, sizeof(flow));
	}

	void addCap(int x, int y, F f) {
		cap[E] = f; flow[E] = 0; to[E] = y; prev[E] = last[x]; last[x] = E; E++;
		cap[E] = 0; flow[E] = 0; to[E] = x; prev[E] = last[y]; last[y] = E; E++;
	}

	bool bfs(int s, int t) {
		for (int i = 0; i < V; i++)
			level[i] = -1;
		queue<int> q;
		q.push(s); level[s] = 0;
		while (!q.empty()) {
			int x = q.front(); q.pop();
			for (int i = last[x]; i != -1; i = prev[i])
				if (level[to[i]] == -1 && cap[i] > flow[i]) {
					q.push(to[i]);
					level[to[i]] = level[x] + 1;
				}
		}
		return (level[t] != -1);
	}

	F dfs(int v, int t, F f) {
		if (v == t) return f;
		for (int i = used[v]; i != -1; used[v] = i = prev[i])
			if (level[to[i]] > level[v] && cap[i] > flow[i]) {
				F tmp = dfs(to[i], t, min(f, cap[i] - flow[i]));
				if (tmp > 0) {
					flow[i] += tmp;
					flow[i ^ 1] -= tmp;
					return tmp;
				}
			}
		return 0;
	}

	F solve(int s, int t) {
		while (bfs(s, t)) {
			for (int i = 0; i < V; i++) used[i] = last[i];
			while (dfs(s, t, inf) != 0);
		}
		F ans = 0;
		for (int i = last[s]; i != -1; i = prev[i])
			ans += flow[i];
		return ans;
	}

	void traS(int u) {
		mkS[u] = true;
		for (int i = last[u], v; i != -1; i = prev[i]) {
			if (cap[i] - flow[i] > 0 && !mkS[v = to[i]]) {
				traS(v);
			}
		}
	}
};
struct Gomory_Hu_Tree {
	int n;
	int mincut[maxV][maxV];
	Dinic mf;

	void init(int n) {
		this->n = n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				mincut[i][j] = i == j ? 0 : inf;
			}
		}
		mf.init(n);
	}

	void addEdge(int a, int b, int c) {
		mf.addCap(a, b, c);
	}

	void output() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d%c", mincut[i][j], j == n - 1 ? '\n' : ' ');
			}
		}
	}

	void solve() {
		vector<int> cur;
		for (int i = 0; i < n; i++)
			cur.PB(i);
		Rec(cur);
		output();
	}

	void Rec(vector<int> cur) {
		if (cur.size() <= 1) return;
		int s = cur[0], t = cur[1];
		mf.reset();
		int cut = mf.solve(s, t);
		mf.traS(s);
		for (int i = 0; i < n; i++) {
			if (mf.mkS[i]) {
				for (int j = 0; j < n; j++) {
					if (!mf.mkS[j]) {
						mincut[i][j] = mincut[j][i] = min(mincut[i][j], cut);
					}
				}
			}
		}
		vector<int> ch[2];
		for (int i = 0; i < cur.size(); i++) {
			int now = cur[i];
			if (mf.mkS[now]) ch[0].PB(now);
			else ch[1].PB(now);
		}
		Rec(ch[0]);
		Rec(ch[1]);
	}

}gh;

//Uva11495
int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case #%d:\n", cas);
		int n;
		scanf("%d", &n);
		gh.init(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int x;
				scanf("%d", &x);
				if (i == j) continue;
				gh.addEdge(i, j, x);
			}
		}
		gh.solve();
	}
	return 0;
}