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

const int inf = 2000000000;
const double eps = 1e-4;
int N, M, K;
int p[33];
LL dist[33][33], d[33][33];
int a[555], b[555], c[555];

void solve1() {
	double ret = 1e50;
	for (int i = 0; i < M; i++) {
		int u = a[i], v = b[i], w = c[i];
		double l = 0.0, r = (double)c[i], ans;
		while (r - l > eps) {
			double mid = (l + r) / 2;
			double Max = check(mid);
			if (sig) {
				ans = mid;
				r = mid;
			} l = mid;
		} 
		if (check(ans)) {
			for (int i = 1; i <= N; i++)
				double tmp = min()
		}
	}
	int cnt = check(ans);
	if (cnt > 1) {
		printf("%.3f ", ans);
		printf("INFINITE\n");
		return;
	}
	printf("%.3f ", ans);
	for (int i = 0; i < M; i++) {
		if (a[i] == anskk) {
			printf("%d %.3f\n", ansk, ans);
			return;
		}
	}
}

void solve2() {
	int ret = inf, ansk, cnt = 0;
	for (int u = 1; u <= N; u++) {
		int sum = 0;
		for (int i = 1; i <= N; i++)
			sum += dist[u][i] * p[i];
		if (sum < ret) {
			ret = sum;
			ansk = u;
			cnt = 1;
		} else if (sum == ret) {
			cnt++;
		}
	}
	if (cnt > 1) {
		printf("INFINITE\n");
		return;
	}
	printf("%d.000 ", ret);
	for (int i = 0; i < M; i++) {
		if (a[i] == ansk) {
			printf("%d 0.000\n", i + 1);
			return;
		}
		if (b[i] == ansk) {
			printf("%d %d.000\n", i + 1, c[i]);
			return;
		}
	}
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	int cas = 1;
	while (Test--) {
		printf("Case %d:\n", cas++);
		scanf("%d%d%d", &N, &M, &K);
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				if (i != j) dist[i][j] = d[i][j] = inf;
				else dist[i][j] = d[i][j] = 0;
		for (int i = 1; i <= N; i++)
			scanf("%d", &p[i]);
		for (int i = 0; i < M; i++) {
			scanf("%d%d%d", &a[i], &b[i], &c[i]);
			d[a[i]][b[i]] = d[b[i]][a[i]] = c[i];
		}

		for (int k = 1; k <= N; k++)
			for (int i = 1; i <= N; i++)
				for (int j = 1; j <= N; j++)
					if (d[i][k] + d[k][j] < d[i][j])
						d[i][j] = d[i][k] + d[k][j];
		for (int k = N - K + 1; k <= N; k++)
			for (int i = 1; i <= N; i++)
				for (int j = 1; j <= N; j++)
					if (d[i][k] + d[k][j] < dist[i][j])
						dist[i][j] = d[i][k] + d[k][j];
		solve1();
		solve2();
	}
	return 0;
}
