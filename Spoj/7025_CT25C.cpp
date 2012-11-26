/*
 * Author: Yang Zhang
 * Created Time: Tue 11 Sep 2012 10:19:55 AM CST
 * File Name: 7025_CT25C.cpp
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

int n, m;
int d[305][305];
int main() {
	while (~scanf("%d", &n)) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &d[i][j]);
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = i + 1; j < n; j++)
					d[j][i] = d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

		scanf("%d", &m);
		for (; m--; ) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			LL ret = 0;
			for (int i = 0; i < n; i++)
				for (int j = i + 1; j < n; j++) {
					if (d[i][a] + c + d[b][j] < d[i][j]) {
						d[i][j] = d[j][i] = d[i][a] + c + d[b][j];
					}
					if (d[i][b] + c + d[a][j] < d[i][j]) {
						d[i][j] = d[j][i] = d[i][b] + c + d[a][j];
					}
					ret += d[i][j];
				}
			printf("%lld\n", ret);
		}
	}
	return 0;
}

