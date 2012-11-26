/*
 * Author: Yang Zhang
 * Created Time: Sun 02 Sep 2012 11:31:39 AM CST
 * File Name: 5874.cpp
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
int n, m;
vector<int> adj[MAXN];
int cx[MAXN], cy[MAXN], mk[MAXN], a[MAXN];

bool dfs(int u) {
	for (int i = 0, v; i < adj[u].size(); i++) {
		if (!mk[v = adj[u][i]]) {
			mk[v] = true;
			if (cy[v] == -1 || dfs(cy[v])) {
				cy[v] = u;
				cx[u] = v;
				return 1;
			}
		}
	}
	return 0;
}

int MaxMatch() {
	int ret = 0;
	memset(cx, -1, sizeof(cx));
	memset(cy, -1, sizeof(cy));
	for (int i = 0; i < n; i++)
		if (cx[i] == -1) {
			memset(mk, 0, sizeof(mk));
			ret += dfs(i);
		}
	return ret;
}

int main() {
	int Test;
	scanf("%d", &Test);
	for (; Test--; ) {
		scanf("%d%d", &n, &m);
		set<int> st;
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			adj[i].clear();
		}
		for (int i = 0; i < m; i++) {
			int x;
			scanf("%d", &x);
			st.insert(x);
		}
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				if (st.find(a[i] + a[j]) != st.end()) {
					adj[i].PB(j); adj[j].PB(i);
				}
		int ret = MaxMatch();
		printf("%d\n", ret / 2);
	}
	return 0;
}

