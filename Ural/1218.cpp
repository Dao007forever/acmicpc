#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 222;
struct person {
	char name[111];
	int a, b, c;
}p[maxn];
struct Edge {
	int v, next;
}edge[maxn * maxn];
int n;
int win[maxn], vis[maxn];
int num, Head[maxn];

void addEdge(int u, int v) {
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}

bool canwin(person A, person B) {
	int ret = 0;
	if (A.a > B.a) ret++;
	if (A.b > B.b) ret++;
	if (A.c > B.c) ret++;
	return ret >= 2;
}

void bfs(int s, int& p) {
	memset(vis, 0, sizeof(vis));
	queue<int> Q;
	vis[s] = true;
	Q.push(s);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		for (int i = Head[u]; i != -1; i = edge[i].next) {
			int v = edge[i].v;
			if (!vis[v]) {
				p++;
				Q.push(v);
				vis[v] = true;
			}
		}
	}
}

int main() {
	freopen("in", "r", stdin);
	num = 0;
	memset(Head, -1, sizeof(Head));
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%s %d %d %d", p[i].name, &p[i].a, &p[i].b, &p[i].c);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i != j && canwin(p[i], p[j])) 
				addEdge(i, j);
	for (int i = 0; i < n; i++)
		bfs(i, win[i]);
	int Max = 0;
	for (int i = 0; i < n; i++)
		Max = max(Max, win[i]);
	for (int i = 0; i < n; i++)
		if (win[i] == Max)
			printf("%s\n", p[i].name);
	return 0;
}
