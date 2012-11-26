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

typedef int F;
#define inf (1 << 29)
#define maxV 10000
#define maxE 400000
struct Dinic {
	int V, E;
	F cap[maxE], flow[maxE];
	int to[maxE], prev[maxE];
	int level[maxV], used[maxV], last[maxV];

	void init(int n) {
		V = n; E = 0;
		for (int i = 0; i < V; i++) last[i] = -1;
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

	void output(int x, int y) {
		int idx = (x - 1) * n + y;
		int ansx = -1, ansy = -1;
		for (int i = last[idx]; i != -1; i = prev[i]) {
			if (flow[i]) {
				int idx = to[i];
				if (idx <= n*n*2) ansx = idx - n*n;
				else ansy = idx - n*n*2;
			}
		}
	}
}mf;

int mat[55][55], row[55][55], col[55][55];
int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		memset(row, 0, sizeof(row));
		memset(col, 0, sizeof(col));
		int n, r, c;
		scanf("%d%d%d", &n, &r, &c);
		mf.init(n*n*3+2);
		int source = 0, sink = n*n*3+1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int x;
				scanf("%d", &x);
				row[i][x] = true;
				col[j][x] = true;
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i <= r && j <= c) continue;
				int idx = (i-1)*n + j;
				mf.addCap(source, idx, 2);
				for (int c = 1; c <= n; c++) {
					if (!row[i][c] && !col[j][c]) {
						int a = n*n + (i-1)*n + c;
						mf.addCap(idx, a, 1);
						int b = n*n*2 + (j-1)*n + c;
						mf.addCap(idx, b, 1);
					}
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			for (int c = 1; c <= n; c++) {
				if (!row[i][c]) {
					int a = n*n + (i-1)*n + c;
					mf.addEdge(a, sink, 1);
				}
			}
		}
		for (int j = 1; j <= n; j++) {
			for (int c = 1; c <= n; c++) {
				if (!col[j][c]) {
					int b = n*n*2 + (j-1)*n + c;
					mf.addEdge(b, sink, 1);
				}
			}
		}
		int flow = mf.solve(source, sink);
		if (flow >= 2 * (n * n - r * c)) {
			puts("YES");
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					if (i <= r && j <= c) printf("%d%c", mat[i][j], j == n ? '\n' : ' ');
					else {
						mf.output(i, j);
					}
				}
			}
		} else {
			puts("NO");
		}
	}
	return 0;
}