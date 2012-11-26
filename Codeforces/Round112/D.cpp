#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 100005
int N, M;
int ex[MAXN], ey[MAXN];
int depth[MAXN], grp[MAXN], deg[MAXN];
vector<int> adj[MAXN], bit[MAXN];

int lowbit(int x)
{
	return x & (-x);
}

void add(int gp, int x, int num)
{
	for (int i = x; i < bit[gp].size(); i += lowbit(i))
		bit[gp][i] += num;
}

int sum(int gp, int x)
{
	int ret = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		ret += bit[gp][i];
	return ret;
}

void dfs(int gp, int lev, int u, int fa)
{
	grp[u] = gp;
	depth[u] = lev;
	bit[gp].push_back(0);
	for (int i = 0; i < adj[u].size(); i++)
		if (adj[u][i] != fa) {
			dfs(gp, lev + 1, adj[u][i], u);
		}
}

int main()
{
	freopen("in.txt", "r", stdin);
	cin >> N;
	for (int i = 1; i < N; i++) {
		cin >> ex[i] >> ey[i];
		deg[ex[i]]++; deg[ey[i]]++;
		adj[ex[i]].push_back(ey[i]);
		adj[ey[i]].push_back(ex[i]);
	}
	int root = 1;
	for (int i = 1; i <= N; i++)
		if (deg[i] > 2)
			root = i;
	for (int i = 0; i < adj[root].size(); i++) {
		bit[i].push_back(0);
		dfs(i, 1, adj[root][i], root);
	}

	for (int i = 1; i < N; i++)
		if (depth[ex[i]] < depth[ey[i]])
			swap(ex[i], ey[i]);
	cin >> M;
	while (M--) {
		int type, idx;
		cin >> type;
		if (type == 1) {
			cin >> idx;
			idx = ex[idx];
			add(grp[idx], depth[idx], -1);
		} else if (type == 2) {
			cin >> idx;
			idx = ex[idx];
			add(grp[idx], depth[idx], 1);
		} else {
			int x, y;
			cin >> x >> y;
			if (grp[x] == grp[y]) {
				if (depth[x] > depth[y]) swap(x, y);
				int val = sum(grp[y], depth[y]) - sum(grp[x], depth[x]);
				if (val > 0) printf("-1\n");
				else printf("%d\n", depth[y] - depth[x]);
			} else {
				int val = sum(grp[y], depth[y]) + sum(grp[x], depth[x]);
				if (val > 0) printf("-1\n");
				else printf("%d\n", depth[y] + depth[x]);
			}
		}
	}
	return 0;
}
