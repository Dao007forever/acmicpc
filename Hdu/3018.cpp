/*
 * Author: Yang Zhang
 * Created Time: Fri 17 Aug 2012 01:19:54 PM UTC
 * File Name: 3018.cpp
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

#define maxn 100005
int p[maxn];
int find(int x) {
	if (p[x] == x) return x;
	return p[x] = find(p[x]);
}
int main() {
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 1; i <= n; i++)
			p[i] = i;
		vector<int> deg(n + 5);
		vector<int> odd(n + 5);
		vector<int> cnt(n + 5);
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			deg[a]++; deg[b]++;
			int pa = find(a), pb = find(b);
			if (pa != pb) p[pa] = pb;
		}
		for (int i = 1; i <= n; i++) {
			int pi = find(i);
			cnt[pi]++;
			if (deg[i] & 1) odd[pi]++;
		}
		int ret = 0;
		for (int i = 1; i <= n; i++)
			if (p[i] == i) {
				if (odd[i] == 0 && cnt[i] > 1) ret++;
				else ret += odd[i] / 2;
			}
		printf("%d\n", ret);
	}
	return 0;
}

