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

int n, d;

int main() {
	freopen("in", "r", stdin);
	bool blank = false;
	int cas = 1;
	while (scanf("%d%d", &n, &d)) {
		if (n == 0 && d == 0) break;

		printf("Case %d: ", cas++);
		double ret = 0;
		int s = 0;
		for (int i = 0; i < n; i++) {
			int p, L, v;
			scanf("%d%d%d", &p, &L, &v);
			ret += 2.0 * (double)L / v;
			s += L;
		}
		ret += (double)d - s;
		printf("%.3f\n", ret);
		puts("");
	}
	return 0;
}
