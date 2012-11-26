#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 2000 + 10;
const int maxm = 500000 + 10;
struct Edge {
	int u, v, next;
}edge[maxm * 2];
int num, Head[maxn];
int n, m;
int w[maxn], deg[maxn];

void addEdge(int u, int v) {
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}

void solve() {
	queue<int> Q;
	for (int i = 1; i <= n; i++)
		if (deg[i] == 0) {
			Q.push(i);
		}
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (int i = Head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].v;
			w[v] += w[u];
			deg[v]--;
			if (deg[v] == 0) {
				Q.push(v);
			}
		}
	}
	for (int i = 1; i <= n; i++)
		printf("%d%c", w[i], i == n ? '\n' : ' ');
}

int main() {
	freopen("in.txt", "r", stdin);
	int Test;
	scanf("%d%", &Test);
	while (Test--) {
		num = 0;
		memset(Head, -1, sizeof(Head));
		memset(deg, 0, sizeof(deg));

		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%d", &w[i]);
		for (int i = 0; i < m; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			addEdge(v, u);
			deg[u]++;
		}
		solve();
	}
	return 0;
}
