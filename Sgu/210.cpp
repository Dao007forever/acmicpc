/*
 * Author: Yang Zhang
 * Created Time: Wed 22 Aug 2012 09:08:29 PM CST
 * File Name: 210.cpp
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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;
#define MAXN 405
int n;
int a[MAXN], id[MAXN], mk[MAXN], cx[MAXN], cy[MAXN];
vector<int> adj[MAXN];
bool cmp(int i, int j) {
	return a[i] > a[j]; 
}
int dfs(int u) {
	for (int i = 0, v; i < adj[u].size(); i++)
		if (!mk[v = adj[u][i]]) {
			mk[v] = 1;
			if (cy[v] == -1 || dfs(cy[v])) {
				cx[u] = v;
				cy[v] = u;
				return 1;
			}
		}
	return 0;
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]), id[i] = i, a[i] *= a[i];
	for (int i = 0; i < n; i++) {
		int k, x;
		scanf("%d", &k);
		while (k--) {
			scanf("%d", &x);
			adj[i].PB(x - 1);
		}
	}
	sort(id, id + n, cmp);
	memset(cx, -1, sizeof(cx));
	memset(cy, -1, sizeof(cy));
	for (int i = 0; i < n; i++)
		if (cx[id[i]] == -1) {
			memset(mk, 0, sizeof(mk));
			dfs(id[i]);
		}
	for (int i = 0; i < n; i++)
		printf("%d%c", cx[i] + 1, i == n - 1 ? '\n' : ' ');
	return 0;
}
