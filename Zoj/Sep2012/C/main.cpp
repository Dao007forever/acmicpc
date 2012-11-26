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

int n;
int mk[222], mate[222];
bool adj[222][222];

int dfs(int u) {
	for (int v = 0; v < n; v++) {
		if (adj[u][v] && !mk[v]) {
			mk[v] = true;
			if (mate[v] == -1 || dfs(mate[v])) {
				mate[v] = u;
				return 1;
			}
		}
	}
	return 0;
}

int maxMatch() {
	memset(mate, -1, sizeof(mate));
	int ret = 0;
	for (int i = 0; i < n; i++) {
		memset(mk, 0, sizeof(mk));
		ret += dfs(i);
	}
	return ret;
}

char st[222][222];
int main(int argc, char const *argv[])
{
	while (cin >> n) {
		for (int i = 0; i < n; i++)
			scanf("%s", st[i]);
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (st[i][j] == 'U') {
					adj[i][j] = 1;
				}
			}
		}
		int ret = maxMatch();
		printf("%s\n", ret == n ? "YES" : "NO");
	}
	return 0;
}