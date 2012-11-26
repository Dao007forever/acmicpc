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

const int maxn = 7200;
struct Edge {
	int v, next;
}edge[30000];
int num, Head[maxn];
int N;
int Find;
int dp[maxn], newdp[maxn], c[3], mk[maxn];
set<int> s[3];
set<int> way[maxn], newway[maxn];

void addEdge(int u, int v) {
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}

void dfs(int x, int v) {
	if (mk[x] + v == 3) {
		Find = false;
		return;
	}
	if (mk[x] == v) return;
	mk[x] = v;
	c[v]++;
	s[v].insert(x);
	for (int i = Head[x]; i != -1; i = edge[i].next)
		dfs(edge[i].v, 3 - v);
}

void DP() {
	memset(newdp, 0, sizeof(newdp));
	for (int i = 0; i < N; i++)
		newway[i].clear();
	for (int i = 1; i <= 2; i++) {
		for (int j = 0; j <= N; j++) 
			if (dp[j] && !newdp[j + c[i]]) {
				newdp[j + c[i]] = true;
				newway[j + c[i]] = newway[j];
				for (set<int>::iterator it = s[i].begin(); it != s[i].end(); it++)
					newway[j + c[i]].insert(*it);
			}
	}
	for (int i = 0; i < N; i++) {
		dp[i] = newdp[i];
		way[i] = newway[i];
	}
}

int main() {
	freopen("in", "r", stdin);
	num = -1;
	memset(Head, -1, sizeof(Head));
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int k, x;
		cin >> k;
		while (k--) {
			cin >> x;
			addEdge(i, x);
		}
	}
	dp[0] = true;
	Find = true;
	for (int i = 1; i <= N; i++)
		if (!mk[i]) {
			c[1] = 0, c[2] = 0;
			s[1].clear(), s[2].clear();
			dfs(i, 1);
			DP();
			if (!Find) {
				cout << "NO SOLUTION" << endl;
				return 0;
			}
		}
	int ans;
	for (ans = N >> 1; !dp[ans]; ans--);
	printf("%d\n", ans);
	for (int i = 1; i <= N; i++)
		if (way[ans].find(i) != way[ans].end())
			printf("%d ", i);
	return 0;
}
