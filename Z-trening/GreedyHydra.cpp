/*
 * 贪吃的九头龙，N个果子，M个头，其中有一个是大头，其他都是小头，要求大头必须吃K个果子，并且包含第一个果子，每两个果子之间的树枝有一个难受值，求难受值的最小值
 * 树形dp，f(1,i,j)包含节点i，大头吃了j个，当前节点由大头吃的最小难受值，f(0,i,j)表示当前节点由小头吃的最小难受值，然后类似背包（好像又叫泛化背包）的方法，用滚动数组记录状态，转移的时候，如果相邻两个点都由大头吃，那么就要加上这条树枝的难受值，如果相邻两个点分别由大头和小头吃，那么不需要加上这条树枝的难受值，如果相邻两个节点都由小头吃，那么还需要讨论M的值，如果M=2，那么也需要加上这条树枝的难受值，因为这条树枝会被一个小头吃掉，而如果M>2，就不需要，因为小头可以交替吃果子，树枝就不会被吃下去了
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

const int maxn = 300 + 5;
const int inf = 1000000000;
int N, M, K;
int cnt[maxn], f[2][maxn][maxn]; 
int pref[2][maxn], tf[2][maxn];
vector<int> adj[maxn];
vector<int> cost[maxn];

void TreeDP(int u, int fa)
{
	cnt[u] = 1;
	for (int i = 0; i < adj[u].size(); i++)
		if (adj[u][i] != fa) {
			TreeDP(adj[u][i], u);
			cnt[u] += cnt[adj[u][i]];
		}
	for (int k = 0; k < 2; k++)
		for (int i = 0; i <= cnt[u]; i++)
			tf[k][i] = inf;
	tf[1][1] = tf[0][0] = 0;

	int now = 1;
	for (int i = 0; i < adj[u].size(); i++)
		if (adj[u][i] != fa) {
			int v = adj[u][i];
			for (int k = 0; k < 2; k++)
				for (int j = 0; j <= now; j++)
					pref[k][j] = tf[k][j];

			for (int k = 0; k < 2; k++)
				for (int j = 0; j <= now; j++)
					tf[k][j] = inf;

			for (int j = 0; j <= now; j++)
				for (int k = 0; k <= cnt[v]; k++) {
					tf[1][j + k] = min(tf[1][j + k], pref[1][j] + f[1][v][k] + cost[u][i]);
					tf[1][j + k] = min(tf[1][j + k], pref[1][j] + f[0][v][k]);
					tf[0][j + k] = min(tf[0][j + k], pref[0][j] + f[1][v][k]);
					tf[0][j + k] = min(tf[0][j + k], pref[0][j] + f[0][v][k] + (M == 2) * cost[u][i]);
				}
			now += cnt[v];
		}
	for (int k = 0; k < 2; k++)
		for (int i = 0; i <= cnt[u]; i++)
			f[k][u][i] = tf[k][i];
}

int main()
{
//	freopen("in", "r", stdin);
	cin >> N >> M >> K;
	for (int i = 1; i < N; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].push_back(b); cost[a].push_back(c);
		adj[b].push_back(a); cost[b].push_back(c);
	}

	if (M + K - 1 > N) {
		cout << -1 << endl;
		return 0;
	}
	TreeDP(1, 0);
	cout << f[1][1][K] << endl;
	return 0;
}


