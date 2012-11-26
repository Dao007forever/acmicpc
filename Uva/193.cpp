/*
 * 一般图最大独立集
 * NP-complete，dfs搜索
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

vector<int> adj[111];
int col[111], ans[111];
int n, m, ret;

void dfs(int cur = 0, int num_w = 0) {
	if (cur == n) {
		if (n - num_w > ret) {
			ret = n - num_w;
			for (int i = 0; i < n; i++)
				ans[i] = col[i];
		}
	} else {
		col[cur] = 1;
		bool ok = true;
		for (int i = 0; i < adj[cur].size() && ok; i++)
			if (col[adj[cur][i]] == col[cur]) ok = false;
		if (ok) dfs(cur + 1, num_w);

		col[cur] = 0;
		dfs(cur + 1, num_w + 1);
	}
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> n >> m;
		for (int i = 0; i < n; i++)
			adj[i].clear();
		while (m--) {
			int a, b;
			cin >> a >> b;
			a--; b--;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		memset(col, -1, sizeof(col));
		ret = 0;
		dfs();
		cout << ret << endl;
		/*v.clear();
		for (int i = 0; i < n; i++)
			if (ans[i] == 1) {
				v.push_back(i);
			}
		for (int i = 0; i < v.size(); i++)
			printf("%d%s", v[i] + 1, i == v.size() - 1 ? "\n" : " ");*/
		int space = 0;
		for (int i = 0; i < n; i++)
			if (ans[i] == 1) {
				if (space) printf(" ");
				space = 1;
				printf("%d", i + 1);
			}
		puts("");
	}
	return 0;
}
