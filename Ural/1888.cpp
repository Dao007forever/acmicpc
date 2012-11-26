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

#define abs(x) ((x) > 0 ? (x) : -(x))
const int inf = 1000000000;
int N, P;
int d[55][55], vis[55], dis[55];
int ok;

void Floyd()
{
	for (int k = 1; k <= P; k++)
		for (int i = 1; i <= P; i++)
			for (int j = 1; j <= P; j++)
				if (i != j && j != k && i != k)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

bool check()
{
	for (int i = 1; i <= P; i++)
		for (int j = 1; j <= P; j++)
			if (i != j && d[i][j] == 1) {
				if (abs(dis[i] - dis[j]) != 1) {
					return false;
				}
			}
	return true;
}

int main()
{
	freopen("in", "r", stdin);
	cin >> N >> P;
	for (int i = 1; i <= P; i++)
		for (int j = 1; j <= P; j++)
			if (i != j) d[i][j] = inf;
	for (int i = 1; i <= N; i++) {
		int a, b;
		cin >> a >> b;
		d[a][b] = d[b][a] = 1;
	}
	Floyd();
	int ret = 0, ki, kj;
	for (int i = 1; i <= P; i++)
		for (int j = 1; j <= P; j++)
			if (i != j && d[i][j] > ret) {
				ret = d[i][j];
				ki = i; kj = j;
			}
	ok = true;
	if (ret == inf) {
		memset(vis, 0, sizeof(vis));
		vis[ki] = vis[kj] = 1;
		dis[ki] = 1;
		for (int i = 1; i <= P; i++)
		if (d[ki][i] != inf) {
			dis[i] = dis[ki] + d[ki][i];
			vis[i] = 1;
		}
		dis[kj] = 50;
		for (int i = 1; i <= P; i++)
		if (d[kj][i] != inf) {
			dis[i] = dis[kj] - d[kj][i];
			vis[i] = 1;
		}
		for (int i = 1; i <= P; i++)
			if (!vis[i]) {
				dis[i] = 1;
				for (int j = 1; j <= P; j++)
					if (d[i][j] != inf) {
						dis[j] = dis[i] + d[i][j];
						vis[j] = 1;
					}
			}
		if (!check()) ok = false;
		if (!ok) {
			printf("-1\n");
		} else {
			printf("49\n");
			for (int i = 1; i <= P; i++)
				printf("%d ", dis[i]);
		}
	} else {
		dis[ki] = 1;
		for (int i = 1; i <= P; i++)
			dis[i] = dis[ki] + d[ki][i];
		if (!check()) ok = false;
		if (!ok) {
			printf("-1\n");
		} else {
			printf("%d\n", ret);
			for (int i = 1; i <= P; i++)
				printf("%d ", dis[i]);
		}
	}
	return 0;
}

