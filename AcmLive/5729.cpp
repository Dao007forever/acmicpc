/*
 * Author: Yang Zhang
 * Created Time: Thu 30 Aug 2012 04:05:10 PM CST
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

const int n = 20;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
struct Rec {
	int x, y, xl, yl;
	Rec() {}
	Rec(int x, int y, int xl, int yl) : x(x), y(y), xl(xl), yl(yl) {}
}rec[25];
char input[25][25];
bool vis[25][25];
int m, id[25];

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < n;
}

void dfs(int x, int y) {
	vis[x][y] = true;
	for (int k = 0; k < 4; k++) {
		int xx = x + dx[k], yy = y + dy[k];
		if (check(xx, yy) && !vis[xx][yy] && input[xx][yy] == 'x')
			dfs(xx, yy);
	}
}

pair<int, int> find() {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (!vis[i][j]) return MP(i, j);
}

int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; Test--; cas++) {
		printf("Case %d: ", cas);
		for (int i = 0; i < n; i++)
			scanf("%s", input[i]);
		memset(vis, 0, sizeof(vis));
		m = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (input[i][j] == 'x' && !vis[i][j]) {
					int xlen = 0, ylen = 0;
					for (int k = i; k < n && input[k][j] == 'x'; k++, xlen++);
					for (int k = j; k < n && input[i][k] == 'x'; k++, ylen++);
					rec[m++] = Rec(i, j, xlen, ylen);
					dfs(i, j);
				}
		for (int i = 0; i < m; i++) id[i] = i;
		int ret = -1;
		do {
			memset(vis, 0, sizeof(vis));
			vector<pair<int, int> > p(m + 5);
			bool flag = true;
			for (int i = 0; i < m && flag; i++) {
				pair<int, int> pos = find();
				int idx = id[i];
				for (int x = 0; x < rec[idx].xl && flag; x++)
					for (int y = 0; y < rec[idx].yl && flag; y++) {
						int xx = pos.first + x, yy = pos.second + y;
						if (xx >= 5 || yy >= 5 || vis[xx][yy]) {
							flag = false;
							break;
						}
						vis[xx][yy] = true;
					}
				p[idx] = pos;
			}

			if (!flag) continue;
			for (int i = 0; i + 5 <= n; i++)
				for (int j = 0; j + 5 <= n; j++) {
					int sum = 0;
					for (int k = 0; k < m; k++) {
						sum += abs(i + p[k].first - rec[k].x) + abs(j + p[k].second - rec[k].y);
					}
					if (ret == -1 || sum < ret) {
						ret = sum;
					}
				}
		} while (next_permutation(id, id + m));
		if (ret == -1) puts("invalid data");
		else printf("%d\n", ret);
	}
	return 0;
}


