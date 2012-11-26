/*
 * Author: Yang Zhang
 * Created Time: Sun 01 Jul 2012 12:33:18 PM UTC
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

const int maxn = 100005;
int n;
int a[maxn];

bool check(int lim) {
	int pa = 0, pb = a[2];
	for (int i = 3; i <= n; i++) {
		if (i & 1) {
			pb = min(a[i], lim - a[1] - pb);
			pa = a[i] - pb;
		} else {
			pa = min(a[i], a[1] - pa);
			pb = a[i] - pa;
		}
	}
	return pa == 0;
}

int main() {
	while (scanf("%d", &n) && n) {
		int ret = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
		}
		for (int i = 1; i <= n; i++) {
			ret = max(ret, a[i] + a[i % n + 1]);
		}

		if (n & 1 == 0) {
			cout << ret << endl;
			continue;
		}
		if (n == 1) {
			cout << a[1] << endl;
			continue;
		}

		int l = ret, r = 300000;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				ret = mid;
				r = mid - 1;
			} else l = mid + 1;
		}
		cout << ret << endl;
	}
	return 0;
}

