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

#define MAXN 200005
const int mod = 1000000009;
int n, m;
int p[MAXN];

int find(int x) {
	return p[x] == x ? x : p[x] = find(p[x]);
}

void Union(int a, int b) {
	p[find(a)] = p[find(b)];
}

int main() {
	freopen("in", "r", stdin);
	scanf("%d%d", &n, &m);
	int ret = 1;
	for (int i = 1; i <= n; i++)
		p[i] = i;
	while (m--) {
		int a, b;
		scanf("%d%d", &a, &b);
		if (find(a) == find(b)) ret = ret * 2 % mod;
		Union(a, b);
		printf("%d\n", ret - 1);
	}
	return 0;
}
