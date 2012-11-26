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

const double eps = 1e-8;
const double inf = 1e9;
const double PI = acos(-1.0);
int n;
double x[33], y[33];

double calc(double ang) {
	double rx1 = -inf, rx2 = inf, ry1 = -inf, ry2 = inf;
	for (int i = 0; i < n; i++) {
		double a = x[i] * cos(ang) + y[i] * sin(ang);
		double b = y[i] * cos(ang) - x[i] * sin(ang);
		rx1 = max(rx1, a);
		rx2 = min(rx2, a);
		ry1 = max(ry1, b);
		ry2 = min(ry2, b);
	}
	return max(rx1 - rx2, ry1 - ry2);
}

void Solve() {
	double Left = 0.0, Right = PI / 2, mid1, mid2;
	while (Right - Left > eps) {
		mid1 = (Left + Right) / 2;
		mid2 = (mid1 + Right) / 2;
		if (calc(mid1) < calc(mid2)) Right = mid2;
		else Left = mid1;
	}
	double r = calc(mid1);
	printf("%.2lf\n", r * r);
}

int main() {
//	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lf%lf", &x[i], &y[i]);
		Solve();
	}
	return 0;
}
