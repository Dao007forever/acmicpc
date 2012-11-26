/*
 * Author : Yang Zhang
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

const int inf = 100000000;
int N, M, R;
int w[111], d[111][111];
vector<pair<int, int> > edge;
vector<int> cost;

int main() {
	freopen("in", "r", stdin);
	cin >> N >> M >> R;
	if (N == 1 && R == 0) {
		cout << 0 << endl;
		return 0;
	}
	for (int i = 1; i <= N; i++)
		cin >> w[i];
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (i != j) d[i][j] = inf;
	for (int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		edge.PB(MP(a, b));
		cost.PB(c);
		d[a][b] = d[b][a] = c;
	}

	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				if (d[i][k] + d[k][j] < d[i][j])
					d[i][j] = d[i][k] + d[k][j];

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (i != j && d[i][j] == inf) {
				cout << -1 << endl;
				return 0;
			}

	LL ret = -1;
	for (int i = 0; i < M; i++) {
		int a = edge[i].first, b = edge[i].second, c = cost[i];
		LL sum1 = 0, sum2 = 0;
		if (c < 2 * R) continue;
		for (int i = 1; i <= N; i++) {
			if (d[a][i] + R < d[b][i] + c - R) {
				sum1 += (long long)w[i] * (d[a][i] + R);
			} else {
				sum1 += (long long)w[i] * (d[b][i] + c - R);
			}
		}

		for (int i = 1; i <= N; i++) {
			if (d[b][i] + R < d[a][i] + c - R) {
				sum2 += (long long)w[i] * (d[b][i] + R);
			} else {
				sum2 += (long long)w[i] * (d[a][i] + c - R);
			}
		}
		LL tmp = min(sum1, sum2);
		if (ret == -1 || tmp < ret) {
			ret = tmp;
		}
	}
	if (ret == -1) {
		cout << ret << endl;
		return 0;
	}

	double ans = ret / 10000.0;
	printf("%.5f\n", ans);
	return 0;
}
