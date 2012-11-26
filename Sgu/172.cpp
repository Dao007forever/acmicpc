#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 200 + 10;
const int maxm = 60000 + 10;
struct Edge {
	int v, next;
}edge[maxm];
int num, Head[maxn];
int flag;
int color[maxn];

void addEdge(int u, int v) {
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}

void dfs(int u, int c) {
	if (color[u]) {
		if (color[u] != c) {
			flag = 0;
			return;
		}
		return;
	}
	color[u] = c;
	for (int i = Head[u]; i != -1; i = edge[i].next) {
		dfs(edge[i].v, 3 - c);
	}
}

int main() {
	freopen("in", "r", stdin);
	int n, m;
	num = 0;
	memset(Head, -1, sizeof(Head));
	scanf("%d%d", &n, &m);
	while (m--) {
		int x, y;
		scanf("%d%d", &x, &y);
		addEdge(x, y);
		addEdge(y, x);
	}
	flag = 1;
	memset(color, 0, sizeof(color));
	for (int i = 1; i <= n; i++) 
	if (!color[i]) {
		dfs(i, 1);
		if (!flag) break;
	}
	if (!flag) {
		printf("no\n");
	} else {
		printf("yes\n");
		vector<int> ans;
		for (int i = 1; i <= n; i++)
			if (color[i] == 1) ans.push_back(i);
		int n = ans.size();
		printf("%d\n", n);
		for (int i = 0; i < n; i++)
			printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
	}
	return 0;
}
