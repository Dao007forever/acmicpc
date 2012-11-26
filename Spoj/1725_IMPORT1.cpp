/*
 * Author: Yang Zhang
 * Created Time: Mon 27 Aug 2012 08:04:12 PM CST
 * File Name: 1725.cpp
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

const LL inf = 1ll << 50;
int n, m;
LL dis[111][111], way[111][111];

int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				dis[i][j] = inf; way[i][j] = 0;
			}
		}
		while (m--) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			dis[a][b] = dis[b][a] = c;
			way[a][b] = way[b][a] = 1;
		}
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					if (i != j && j != k && k != i) {
						if (dis[i][k] + dis[k][j] < dis[i][j]) {
							dis[i][j] = dis[i][k] + dis[k][j];
							way[i][j] = way[i][k] * way[k][j];
						} else if (dis[i][k] + dis[k][j] == dis[i][j]) {
							way[i][j] += way[i][k] * way[k][j];
						}
					}
		for (int v = 1; v <= n; v++) {
			double ret = 0;
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++) {
					if (v != i && i != j && j != v) {
						if (dis[i][v] + dis[v][j] == dis[i][j]) {
							ret += (double)way[i][v] * way[v][j] / way[i][j];
						}
					}
				}
			printf("%.3f\n", ret);
		}
	}
	return 0;
}

