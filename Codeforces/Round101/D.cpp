#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 200000 + 10;
struct node {
	int x, y, w;
	node() {};
	node(int x, int y, int w): x(x), y(y), w(w) {}  
	bool operator < (node const &T) const {
		return y > T.y;
	}
};

struct ramp {
	int x, d, t, p;
	void init() {
		scanf("%d%d%d%d", &x, &d, &t, &p);
	}
};

struct Edge {
	int u, v, w, z, next;
}edge[4 * MAXN];

int n, m, L, st, ed, x, y, ret;
int Head[MAXN], num;
int f[MAXN], d[MAXN], p[MAXN], ans[MAXN];
ramp a[MAXN];
node cur;
priority_queue<node> q;

void addedge(int u, int v, int w, int z) {
	edge[num].u = u;
	edge[num].v = v;
	edge[num].w = w;
	edge[num].z = z;
	edge[num].next = Head[u];
	Head[u] = num++;
}

int main() {
	freopen("in.txt", "r", stdin);
	memset(Head, -1, sizeof(Head));
	num = 0;
	
	scanf("%d%d", &n, &L);
	int m = 0;
	for (int i = 0; i < n; i++) {
		a[i].init();
		p[m++] = a[i].x - a[i].p;
		p[m++] = a[i].x + a[i].d;
	}
	p[m++] = 0;
	p[m++] = L;
	sort(p, p + m);
	m = unique(p, p + m) - p;

	for (int i = 0; i < m - 1; i++)
		if (p[i] >= 0) {
			addedge(i, i + 1, p[i + 1] - p[i], 0);
			addedge(i + 1, i, p[i + 1] - p[i], 0);
		}

	for (int i = 0; i < n; i++) {
		if (a[i].p > a[i].x) continue;
		x = lower_bound(p, p + m, a[i].x - a[i].p) - p;
		y = lower_bound(p, p + m, a[i].x + a[i].d) - p;
		addedge(x, y, a[i].t + a[i].p, i + 1);
	}

	for (int i = 0; i < m; i++) {
		if (p[i] == 0) st = i;
		if (p[i] == L) ed = i;
		d[i] = (1 << 30);
	}

	q.push(node(st, 0, 0));
	while (!q.empty()) {
		cur = q.top();
		q.pop();
		if (d[cur.x] != (1 << 30)) continue;
		d[cur.x] = cur.y;
		f[cur.x] = cur.w;
		for (int i = Head[cur.x]; i != -1; i = edge[i].next) {
			q.push(node(edge[i].v, cur.y + edge[i].w, i));
		}
	}

	printf("%d\n", d[ed]);
	x = ed;
	ret = 0;
	while (x != st) {
		if (edge[f[x]].z) ans[ret++] = edge[f[x]].z;
		x = edge[f[x]].u;
	}
	printf("%d\n", ret);
	for (int i = ret - 1; i >= 0; i--)
		printf("%d%c", ans[i], i ? ' ' : '\n');
	return 0;
}
