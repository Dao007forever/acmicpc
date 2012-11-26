/*
 * Author: Yang Zhang
 * Created Time: Thu 30 Aug 2012 08:57:16 PM CST
 * File Name: 5724.cpp
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

int n = 0;
int node[10005];
void dfs(int l, int r) {
	if (l > r) return;
	if (l == r) {
		printf("%d\n", node[l]);
		return;
	}
	int m = l + 1;
	for (; node[m] < node[l] && m <= r; m++);
	dfs(l + 1, m - 1);
	dfs(m, r);
	printf("%d\n", node[l]);
}
int main() {
	for (; ~scanf("%d", &node[n]); n++);
	dfs(0, n - 1);
	return 0;
}

