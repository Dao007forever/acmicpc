/*
 * 一棵树，从中选择尽量多的边，但要保证每个点的度不大于1
 * 树形DP，f(i,0)表示以i为根且i的度为0的最大值，f(i,1)表示以i为根且i的度为1的最大值，显然，f(i,1)>=f(i,0)，于是f(u,0)=sigma(f(son[u],1))，f(u,1)=max{f(u,0)-f(son[u],1)+f(son[u],0)+1}，同时记录路径
 */
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

const int maxn = 200005;
int N, M;
int f[maxn][2], pre[maxn][2];
vector<int> adj[maxn];
set<pair<int, int> > mset;

void dfs(int u, int fa) 
{
	for (int i = 0; i < adj[u].size(); i++)
		if (adj[u][i] != fa) {
			dfs(adj[u][i], u);
			f[u][0] += f[adj[u][i]][1];
		}
	for (int i = 0; i < adj[u].size(); i++)
		if (adj[u][i] != fa) {
			int v = adj[u][i];
			if (f[u][0] - f[v][1] + f[v][0] + 1 > f[u][1]) {
				f[u][1] = f[u][0] - f[v][1] + f[v][0] + 1;
				pre[u][1] = v;
			}
		}
}

void Print(int u, int fa, int flag)
{
	for (int i = 0; i < adj[u].size(); i++)
		if (adj[u][i] != fa) {
			int v = adj[u][i];
			if (v == pre[u][1] && flag) {
				pair<int, int> tmp(u, v);
				if (mset.find(tmp) != mset.end()) {
					cout << u << " " << v << endl;
				} else {
					cout << v << " " << u << endl;
				}
				Print(v, u, 0);
			} else {
				Print(v, u, 1);
			}
		}
}

int main()
{
	freopen("in", "r", stdin);
	cin >> N >> M;
	for (; M--; ) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
		mset.insert(make_pair(a, b));
	}
	memset(f, 0, sizeof(f));
	memset(pre, 0, sizeof(pre));
	dfs(1, 0);
	cout << f[1][1] << endl;
	Print(1, 0, 1);
	return 0;
}
