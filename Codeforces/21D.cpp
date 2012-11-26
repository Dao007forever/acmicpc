/*
 * 求从节点1出发经过每条边至少一次的最短回路
 * 如果所有点的度均为偶数，那么所有点正好经过一遍回到起点，即为欧拉回路，如果有某些点度为奇数，那么这些奇度点两两之间的最短路径肯定还要再经过一遍，然后用状态压缩dp求出这些奇度点两两之间的最短距离的和
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

const int inf = 1000000000;
int N, M;
long long dp[1 << 16];
long long dist[16][16];
int deg[16];
long long ret;
vector<pair<int, int> > edge;

void Floyd() {
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
}

long long DP(int mask) {
	if (dp[mask] >= 0) return dp[mask];

	dp[mask] = inf;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if ((mask & (1 << i)) && (mask & (1 << j)))
				dp[mask] = min(dp[mask], dist[i][j] + DP((mask ^ (1 << i)) ^ (1 << j)));
	return dp[mask];
}

int main() {
	freopen("in", "r", stdin);
	ret = 0;
	cin >> N >> M;
	memset(deg, 0, sizeof(deg));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			dist[i][j] = inf;
	for (int i = 0; i < M; i++) {
		int a, b;
		long long c;
		cin >> a >> b >> c;
		a--; b--;
		edge.push_back(make_pair(a, b));
		deg[a]++; deg[b]++;
		dist[a][b] = dist[b][a] = min(dist[a][b], c);
		ret += c;
	}
	Floyd();
	int mask = 0;
	for (int i = 0; i < N; i++)
		if (deg[i] & 1) mask |= (1 << i);
	memset(dp, 0xff, sizeof(dp));
	dp[0] = 0;
	ret += DP(mask);

	for (int i = 0; i < edge.size(); i++)
		if (edge[i].first != 0 && dist[0][edge[i].first] >= inf)
			ret = -1;
	if (ret >= inf) ret = -1;
	cout << ret << endl;
	return 0;
}
