/*
 * Author: Yang Zhang
 * Created Time: Sat 25 Aug 2012 07:50:13 PM CST
 * File Name: 3118.cpp
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

#define maxn 15
int n, m;
int adj[maxn][maxn];
int f[1 << 16];
int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		memset(adj, 0, sizeof(adj));
		scanf("%d%d", &n, &m);
		while (m--) {
			int a, b;
			scanf("%d%d", &a, &b);
			adj[a][b]++; adj[b][a]++;
		}
		for (int s = 0; s < (1 << n); s++) {
			int cnt = 0;
			for (int i = 0; i < n; i++)
				for (int j = i + 1; j < n; j++)
					if ((s & (1 << i)) && (s & (1 << j))) {
						cnt += adj[i][j];
					}
			f[s] = cnt;
		}
		int ret = 1000000;
		for (int s = 0; s < (1 << n); s++) {
			int tmp = f[s] + f[((1 << n) - 1) ^ s];
			ret = min(ret, tmp);
		}
		printf("%d\n", ret);
	}
	return 0;
}

