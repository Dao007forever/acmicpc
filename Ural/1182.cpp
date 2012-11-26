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

const int maxn = 205;
int N;
int adj[maxn][maxn], mk[maxn], c[3];
int dp[maxn], newdp[maxn];
int Find;
set<int> s[3];
set<int> way[maxn], newway[maxn];

void dfs(int x, int v) {
	if (mk[x] + v == 3) {
		Find = false;
		return;
	}
	if (mk[x] == v) return;
	mk[x] = v;
	c[v]++;
	s[v].insert(x);
	for (int i = 1; i <= N; i++)
		if (adj[x][i]) dfs(i, 3 - v);
}

void DP() {
	memset(newdp, 0, sizeof(newdp));
	for (int i = 0; i < maxn; i++)
		newway[i].clear();

	for (int i = 1; i <= 2; i++) {
		for (int j = 0; j <= N; j++) {
			if (dp[j] && !newdp[j + c[i]]) {
				newdp[j + c[i]] = true;
				newway[j + c[i]] = way[j];
				for (set<int>::iterator it = s[i].begin(); it != s[i].end(); it++) 
					newway[j + c[i]].insert(*it);
			}
		}
	}
	for (int i = 0; i < maxn; i++) {
		dp[i] = newdp[i];
		way[i] = newway[i];
	}
}

int main() {
	freopen("in", "r", stdin);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		int x;
		while (scanf("%d", &x) && x) {
			adj[i][x] = true;
		}
	}
	for (int i = 1; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
			if (adj[i][j] && adj[j][i])
				adj[i][j] = adj[j][i] = false;
			else adj[i][j] = adj[j][i] = true;
	dp[0] = true;
	Find = true;
	for (int i = 1; i <= N; i++) 
	if (!mk[i]) {
		c[1] = 0, c[2] = 0;
		s[1].clear(), s[2].clear();
		dfs(i, 1);
		DP();
		if (!Find) {
			cout << "No solution" << endl;
			return 0;
		}
	}
	int ans;
	for (ans = N >> 1; !dp[ans]; ans--);
	printf("%d ", ans);
	for (int i = 1; i <= N; i++)
		if (way[ans].find(i) != way[ans].end())
			cout << i << " ";
	cout << endl;
	printf("%d ", N - ans);
	for (int i = 1; i <= N; i++)
		if (way[ans].find(i) == way[ans].end())
			cout << i << " ";
	cout << endl;
	return 0;
}
