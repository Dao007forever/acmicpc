/*
 * 简单的状压DP，但是最后一个点只有写成递归的形式才能过，否则会TLE
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

int N;
//int power[21];
//double dp[2][1 << 20];
double pro[21][21], ans[1 << 21];
bool vis[1 << 21];
//int que[10000000][2];

double DP(int d, int s)
{
	if (d == N) return 1.0;

	if (vis[s]) return ans[s];
	vis[s] = 1;
	double &ret = ans[s];
	ret = 0.0;
	for (int i = 0; i < N; i++)
		if ((s & (1 << i)) == 0) {
			double tmp = pro[d][i] * DP(d + 1, s | (1 << i));
			if (tmp > ret) ret = tmp;
		}
	return ret;
}

int main()
{
//	freopen("in", "r", stdin);
	cin >> N;
/*	power[0] = 1;
	for (int i = 1; i <= N; i++)
		power[i] = power[i - 1] * 2;*/
	for (int i = 0; i < N; i++) 
		for (int j = 0; j < N; j++) {
			scanf("%lf", &pro[i][j]);
			pro[i][j] /= 100.0;
		}
/*	int l = 0, r = 0;
	for (int i = 0; i < N; i++) {
		dp[0][power[i]] = pro[0][i];
		que[r][0] = 0, que[r++][1] = power[i];
	}

	while (l <= r) {
		int i = que[l][0], s = que[l++][1];
		int p = i % 2, q = 1 - p;
		if (i == N - 1) {
			break;
		}
		for (int j = 0; j < N; j++)
			if ((s & power[j]) == 0) {
				int news = s | power[j];
				if (dp[p][s] * pro[i + 1][j] > dp[q][news]) {
					dp[q][news] = dp[p][s] * pro[i + 1][j];
					que[r][0] = i + 1, que[r++][1] = news;
				}
			}
	}*/

	/*for (int i = 0; i < N - 1; i++) {
		int p = i % 2, q = 1 - p;
		for (int s = 0; s < 1 << N; s++)
			if (dp[p][s] > 0) {
				for (int j = 0; j < N; j++)
					if ((s & (1 << j)) == 0) {
						int news = s | (1 << j);
						dp[q][news] = max(dp[q][news], dp[p][s] * pro[i + 1][j]);
					}
			}
	}*/
	//printf("%.6f\n", 100.0 * dp[(N - 1) % 2][(1 << N) - 1]);
	double ret = DP(0, 0);
	printf("%.6f\n", ret * 100.0);
	return 0;
}
