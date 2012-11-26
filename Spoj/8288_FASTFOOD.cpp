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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define MAXN 100005
const int inf = 0x3f3f3f3f;
struct SegTree {
	struct node {
		int l, r, Min;
	}T[MAXN << 2];
	int n;

	int lson(int rt) {return rt << 1;}
	int rson(int rt) {return rt << 1 | 1;}

	void pushUp(int rt) {
		T[rt].Min = min(T[lson(rt)].Min, T[rson(rt)].Min);
	}

	void build(int l, int r, int rt) {
		T[rt].l = l; T[rt].r = r; T[rt].Min = inf;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(l, mid, lson(rt));
		build(mid + 1, r, rson(rt));
	}

	void update(int p, int c, int rt) {
		if (T[rt].l == T[rt].r) {
			T[rt].Min = min(c, T[rt].Min);
			return;
		}
		int mid = (T[rt].l + T[rt].r) >> 1;
		if (p <= mid) update(p, c, lson(rt));
		else update(p, c, rson(rt));
		pushUp(rt);
	}

	int query(int L, int R, int rt) {
		if (L <= T[rt].l && T[rt].r <= R) {
			return T[rt].Min;
		}
		int mid = (T[rt].l + T[rt].r) >> 1;
		int ret = inf;
		if (L <= mid) ret = min(ret, query(L, R, lson(rt)));
		if (R > mid) ret = min(ret, query(L, R, rson(rt)));
		return ret;
	}
}tree;

int n, m, q;
int dis[MAXN], vis[MAXN];
vector<pair<int, int> > adj[MAXN];
priority_queue<pair<int, int> > pq;

void addEdge(int u, int v, int w) {
	adj[u].PB(MP(v, w));
}

void dijkstra(int st) {
	for (int i = 0; i < n; i++) {
		dis[i] = inf; vis[i] = false;
	}
	dis[st] = 0;
	pq.push(MP(0, st));
	while (!pq.empty()) {
		int u = pq.top().second; pq.pop();
		vis[u] = true;
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first, w = adj[u][i].second;
			if (!vis[v] && dis[u] + w < dis[v]) {
				dis[v] = dis[u] + w;
				pq.push(MP(-dis[v], v));
			}
		}
	}
}

struct node {
	int a, b, c, id;
}p[MAXN];
bool better[MAXN];
bool cmp(const node &A, const node &B) {
	return A.c < B.c;
}
int main(int argc, char const *argv[])
{
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++) adj[i].clear();
		int A, B, C;
		scanf("%d%d%d", &A, &B, &C);
		A--; B--; C--;
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			addEdge(a, b, c);
			addEdge(b, a, c);
		}
		dijkstra(A);
		for (int i = 0; i < n; i++)
			p[i].a = dis[i];
		dijkstra(B);
		for (int i = 0; i < n; i++)
			p[i].b = dis[i];
		dijkstra(C);
		for (int i = 0; i < n; i++)
			p[i].c = dis[i];

		memset(better, 0, sizeof(better));
		vector<pair<int, int> > x;
		for (int i = 0; i < n; i++) {
			p[i].id = i + 1;
			x.PB(MP(p[i].a, i));
		}
		sort(x.begin(), x.end());
		int r = 1;
		p[x[0].second].a = r;
		for (int i = 1; i < n; i++) {
			if (x[i].first != x[i - 1].first) {
				r++;
			}
			p[x[i].second].a = r;
		}

		tree.build(0, n, 1);
		sort(p, p + n, cmp);
		for (int i = 0; i < n; ) {
			int j = i;
			for (; j + 1 < n && p[j].c == p[j + 1].c; j++) {
				int tmp = tree.query(0, p[j].a - 1, 1);
				if (tmp >= p[j].b) {
					better[p[j].id] = true;
				}
			}
			if (j < n) {
				int tmp = tree.query(0, p[j].a - 1, 1);
				if (tmp >= p[j].b) {
					better[p[j].id] = true;
				}
			}
			j = i;
			for (; j + 1 < n && p[j].c == p[j + 1].c; j++) {
				tree.update(p[j].a, p[j].b, 1);
			}
			if (j < n) {
				tree.update(p[j].a, p[j].b, 1);
			}
			i = j + 1;
		}

		scanf("%d", &q);
		while (q--) {
			int idx;
			scanf("%d", &idx);
			printf("%s\n", better[idx] ? "YES" : "NO");
		}
	}
	return 0;
}