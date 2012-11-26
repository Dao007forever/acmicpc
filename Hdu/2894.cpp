/*
 * Author: Yang Zhang
 * Created Time: Fri 17 Aug 2012 11:02:12 AM UTC
 * File Name: 2894.cpp
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

int n;
bool vis[1 << 12];
vector<int> ans;
void dfs(int u) {
	int v = ((u << 1) & ((1 << n) - 1));
	if (!vis[v]) {
		vis[v] = true;
		dfs(v);
		ans.PB(0);
	}
	if (!vis[v + 1]) {
		vis[v + 1] = true;
		dfs(v + 1);
		ans.PB(1);
	}
}
int main() {
	while (~scanf("%d", &n)) {
		ans.clear();
		memset(vis, 0, sizeof(vis));
		printf("%d ", 1 << n);
		if (n == 1) {
			puts("0");
			continue;
		}
		if (n == 2) {
			puts("0011");
			continue;
		}
		dfs(0);
		for (int i = 1; i < n; i++)
			putchar('0');
		reverse(ans.begin(), ans.end());
		for (int i = 0; i < ans.size() - (n - 1); i++)
			printf("%d", ans[i]);
		puts("");
	}
	return 0;
}

