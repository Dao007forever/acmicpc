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

#define MAXN 1005
const double inf = 1e50;
int n;
int x[MAXN], y[MAXN], z[MAXN], p[MAXN];

bool check(double lim) {
	double A = -inf, C = -inf, E = -inf, G = -inf;
	double B = inf, D = inf, F = inf, H = inf;
	for (int i = 0; i < n; i++) {
		A = max(A, (double)x[i] + y[i] + z[i] - p[i] * lim);
		B = min(B, (double)x[i] + y[i] + z[i] + p[i] * lim);
		C = max(C, (double)x[i] + y[i] - z[i] - p[i] * lim);
		D = min(D, (double)x[i] + y[i] - z[i] + p[i] * lim);
		E = max(E, (double)x[i] - y[i] + z[i] - p[i] * lim);
		F = min(F, (double)x[i] - y[i] + z[i] + p[i] * lim);
		G = max(G, (double)(-x[i]) + y[i] + z[i] - p[i] * lim);
		H = min(H, (double)(-x[i]) + y[i] + z[i] + p[i] * lim);
	}
	return (A < B && C < D && E < F && G < H);
}

int main() {
	freopen("in", "r", stdin);
	int Test, cas = 1;
	cin >> Test;
	while (Test--) {
		printf("Case #%d: ", cas++);
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> x[i] >> y[i] >> z[i] >> p[i];
		double l = 0, r = 1e9, ret;
		while (r - l > 1e-8) {
			double mid = (l + r) / 2;
			if (check(mid)) {
				ret = mid;
				r = mid;
			}
			else l = mid;
		}
		printf("%.6f\n", ret);
	}
	return 0;
}
