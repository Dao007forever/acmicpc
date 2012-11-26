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

int n, m, v;
int main() {
	freopen("in", "r", stdin);
	int cas = 1;
	while (scanf("%d%d%d", &n, &m, &v)) {
		if (n == 0 && m == 0 && v == 0) break;
		printf("Case %d: ", cas++);
		double ret = 0;
		for (int i = 0; i < n; i++) {
			double x, y;
			scanf("%lf%lf", &x, &y);
			double tmp = x * (100.0 - y) / 100.0;
			tmp /= (double)v;
			ret += tmp;
		}
		printf("%.2f\n", ret);
		puts("");
	}
	return 0;
}
