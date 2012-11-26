/*
 * Author: Yang Zhang
 * Created Time: Fri 01 Jun 2012 10:27:14 PM UTC
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
struct move {
	int a, b, c;
}P[128];
const int dx[8] = {0, 0, -1, -1, -1, 1, 1, 1};
const int dy[8] = {-1, 1, 1, -1, 0, -1, 1, 0};
int bitcnt[1 << 16];
LL dp[1 << 16];
int r, c, n, cnt;

int ID(int x, int y) {
	return x * c + y;
}

bool valid(int x, int y) {
	return (x >= 0 && x < r && y >= 0 && y < c);
}

LL dfs(int state){
	if (dp[state] != -1) return dp[state];
	if (bitcnt[state] == 1) return dp[state] = 1;
	dp[state] = 0;
	for (int i = 0; i < cnt; i++) {
		if ((state & (1 << P[i].a)) && (state & 1 << P[i].b) && !(state & (1 << P[i].c)))
			dp[state] += dfs(state ^ (1 << P[i].a) ^ (1 << P[i].b) ^ (1 << P[i].c));
	}
	return dp[state];
}

void work() {
	scanf("%d%d%d", &r, &c, &n);
	int start = 0;
	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--; y--;
		int tmp = ID(x, y);
		start ^= (1 << tmp);
	}
	cnt = 0;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			for (int k = 0; k < 8; k++) {
				int x = i + dx[k], y = j + dy[k];
				int xx = x + dx[k], yy = y + dy[k];
				if (!valid(x, y) || !valid(xx, yy)) continue;
				P[cnt].a = ID(i, j);
				P[cnt].b = ID(x, y);
				P[cnt].c = ID(xx, yy);
				cnt++;
			}
	memset(dp, -1, sizeof(dp));
	LL ret = dfs(start);
	printf("%lld\n", ret);
}
int main() {
	for (int i = 1; i < (1 << 16); i++)
		bitcnt[i] = bitcnt[i >> 1] + (i & 1);
	int Test;
	scanf("%d", &Test);
	for (int i = 1; i <= Test; i++) {
		printf("Case %d: ", i);
		work();
	}
	return 0;
}

