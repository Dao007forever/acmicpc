/*
 * Author: Yang Zhang
 * Created Time: Sat 08 Sep 2012 09:39:46 PM CST
 * File Name: 3108_GRAPHGAM.cpp
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

const int inf = 100000;
int N, K;
int dis[105][105], minR[105], maxR[105];

int main() {
	int Test;
	scanf("%d", &Test);
	for (; Test--; ) {
		scanf("%d%d", &N, &K);
		for (int i = 0; i < N; i++) {
			char st[105];
			scanf("%s", st);
			for (int j = 0; j < N; j++)
				if (st[j] == 'Y') dis[i][j] = 1;
				else if (i == j) {
					dis[i][j] = 0;
				} else {
					dis[i][j] = inf;
				}
		}

		for (int k = 0; k < N; k++)
			for (int i = 0; i < N; i++)
				for (int j = 0; j < N; j++)
					if (i != j && j != k && k != i) {
						dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
					}
		for (int i = 0; i < N; i++) {
			minR[i] = dis[0][i];
			maxR[i] = 0;
			for (int j = 0; j < N; j++)
				maxR[i] = max(maxR[i], dis[i][j]);
		}
		int ret = inf;
		for (int i = 0; i < N; i++) {
			if (minR[i] == inf) continue;
			if (maxR[i] > K) continue;
			if (minR[i] + maxR[i] <= K) ret = min(ret, minR[i] + maxR[i]);
			else ret = min(ret, K + maxR[i]);
		}
		if (ret >= inf) puts("INFINITE GAME");
		else printf("%d\n", ret);
	}
	return 0;
}

