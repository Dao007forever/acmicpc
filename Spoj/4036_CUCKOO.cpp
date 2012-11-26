/*
 * Author: Yang Zhang
 * Created Time: Thu 06 Sep 2012 03:32:50 PM CST
 * File Name: 4036_CUCKOO.cpp
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

#define MAXN 10005
int m, n;
int a[MAXN][2], mate[MAXN];
bool mk[MAXN];

bool dfs(int u) {
	for (int i = 0, v; i < 2; i++)
		if (!mk[v = a[u][i]]) {
			mk[v] = true;
			if (mate[v] == -1 || dfs(mate[v])) {
				mate[v] = u;
				return true;
			}
		}
	return false;
}

int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%d%d", &a[i][0], &a[i][1]);
		bool flag = true;
		memset(mate, -1, sizeof(mate));
		for (int i = 0; i < n; i++) {
			memset(mk, 0, sizeof(mk));
			if (!dfs(i)) {
				flag = false;
				break;
			}
		}
		printf("%s\n", flag ? "successful hashing" : "rehash necessary");
	}
	return 0;
}

