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

int f[21][1111];
int p[21];
int n, m;

int main() {
	freopen("in.txt", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &m, &n);
		p[0] = 1;
		for (int i = 0; i <= n; i++)
			p[i] = p[i - 1] * 10 % m;

		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for (int i = 0; i < 10; i++)
			f[1][(i % m)]++;
		for (int i = 0; i + 2 <= n; i++)
			for (int j = 0; j < m; j++)
				if (f[i][j]) {
					for (int k = 0; k < 10; k++) {
						int tmp = (k % m + p[i + 1] % m + k % m + j % m) % m;
						if (k == 0) f[i + 2][tmp] = f[i][j];
						else f[i + 2][tmp] += f[i][j];
					}
				}
		printf("%d\n", f[n][0]);
	}
	return 0;
}
