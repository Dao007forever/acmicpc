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

#define MAXN 405
const LL mod = 100000007;
int n, m, K;
LL dp[MAXN][MAXN][2], f[MAXN][MAXN][2];
std::vector<int> adj[MAXN];

void update(LL &a, LL b) {
	a += b;
	if (a >= mod) a -= mod;
}

void dfs(int u, int fa) {
	std::vector<int> child;
	for (int i = 0, v; i < adj[u].size(); i++) {
		if ((v = adj[u][i]) != fa) {
			dfs(v, u);
			child.PB(v);
		}
	}

	int len = SZ(child);
	for (int i = 0; i <= len; i++) {
		for (int j = 0; j <= K; j++) {
			f[i][j][0] = f[i][j][1] = 0;
		}
	}
	f[0][0][0] = 1;
	for (int i = 0; i < len; i++) {
		for (int j = 0; j <= K; j++) {
			for (int q = 0; j + q <= K; q++) {
				if (f[i][j][0]) {
					update(f[i + 1][j + q][0], f[i][j][0] * dp[child[i]][q][0] % mod);
					if (j + q + 1 <= K) {
						update(f[i + 1][j + q + 1][1], f[i][j][0] * dp[child[i]][q][1] % mod);
					}
				}
				if (f[i][j][1]) {
					update(f[i + 1][j + q][1], f[i][j][1] * dp[child[i]][q][0] % mod);
				}
			}
		}
	}
	for (int i = 0; i <= K; i++) {
		dp[u][i][0] = (f[len][i][0] + f[len][i][1]) % mod;
		dp[u][i][1] = f[len][i][0];
	}
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d%d", &n, &m, &K);
		for (int i = 0; i < n; i++) adj[i].clear();
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			a--; b--;
			adj[a].PB(b);
			adj[b].PB(a);
		}
		memset(dp, -1, sizeof(dp));
		dfs(0, -1);
		cout << dp[0][K][0] << endl;
	}
	return 0;
}