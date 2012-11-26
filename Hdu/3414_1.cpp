/*
 * Author: Yang Zhang
 * Created Time: Thu 16 Aug 2012 09:48:35 PM UTC
 * File Name: 3414.cpp
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

#define maxn 1005
list<int> path;
int n;
bool g[maxn][maxn];
bool hamilton(int start) {
	path.clear();
	path.PB(start);
	list<int>::iterator cur, pre;
	for (int i = 1; i <= n; i++) {
		if (i == start) continue;
		cur = path.begin();
		if (g[i][*cur]) {
			path.push_front(i);
			continue;
		}
		cur = path.end(); cur--;
		if (g[*cur][i]) {
			path.PB(i);
			continue;
		}

		pre = cur = path.begin();
		cur++;
		for (; cur != path.end(); cur++, pre++) {
			if (g[*pre][i] && g[i][*cur]) {
				path.insert(cur, i);
				break;
			}
		}
	}
	pre = path.begin(); cur = path.end(); cur--;
	if (g[*cur][*pre]) {
		for (list<int>::iterator it = path.begin(); it != path.end(); it++) {
			if (it != path.begin()) printf(" ");
			printf("%d", *it);
		}
		puts("");
		return true;
	}
	return false;
}

int main() {
	while (scanf("%d", &n) && n) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				int x;
				scanf("%d", &x);
				g[i][j] = x;
			}
		if (n == 1) {
			printf("1\n");
			continue;
		}
		bool flag = false;
		for (int i = 1; i <= n && !flag; i++) {
			if (hamilton(i)) {
				flag = true;
			}
		}
		if (!flag) puts("-1");
	}
	return 0;
}

