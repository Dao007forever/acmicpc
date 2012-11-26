/*
 * Author: Yang Zhang
 * Created Time: Fri 29 Jun 2012 07:08:02 PM UTC
 * File Name: main.cpp
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
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
char mat[22][22];
bool vst[22][22];
char land;

int paint(int x, int y) {
	if (vst[x][y]) return 0;
	vst[x][y] = true;
	int cnt = 1;
	if (x && mat[x - 1][y] == land) cnt += paint(x - 1, y);
	if (x + 1 < n && mat[x + 1][y] == land) cnt += paint(x + 1, y);
	if (mat[x][(y - 1 + m) % m] == land) cnt += paint(x, (y - 1 + m) % m);
	if (mat[x][(y + 1) % m] == land) cnt += paint(x, (y + 1) % m);
	return cnt;
}
int main() {
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < n; i++)
			scanf("%s", mat[i]);
		int sx, sy;
		scanf("%d%d", &sx, &sy);
		memset(vst, 0, sizeof(vst));
		int ret = 0;
		land = mat[sx][sy];
		paint(sx, sy);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (mat[i][j] == land) {
					int tmp = paint(i, j);
					ret = max(ret, tmp);
				}

		cout << ret << endl;
	}
	return 0;
}

