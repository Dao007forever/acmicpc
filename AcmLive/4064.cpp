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

const int MAXN = 1200 + 10;
const double PI = acos(-1.0);
const double eps = 1e-8;
struct Point {
	double x, y, ang;
}ps[2 * MAXN];
double x[MAXN], y[MAXN];
int N, M;

int sig(double d) {
	return (d > eps) - (d < -eps);
}

bool cmp(const Point &a, const Point &b) {
	return a.ang < b.ang;
}

int main() {
	freopen("in", "r", stdin);
	int cas = 1;
	while (scanf("%d", &N) && N) {
		printf("Scenario %d:\n", cas++);

		for (int i = 0; i < N; i++) {
			scanf("%lf%lf", &x[i], &y[i]);
		}

		long long ans = (long long)N * (N - 1) * (N - 2) / 6;
		for (int i = 0; i < N; i++) {
			M = 0;
			for (int j = 0; j < N; j++) 
			if (i != j) {
				ps[M].x = x[j] - x[i];
				ps[M].y = y[j] - y[i];
				ps[M].ang = atan2(ps[M].y, ps[M].x);
				M++;
			}

			sort(ps, ps + M, cmp);
			for (int j = 0; j < M; j++) {
				ps[M + j] = ps[j];
				ps[M + j].ang = ps[j].ang + 2 * PI;
			}
			for (int j = 0, l = 0, r = 0; j < M; j++) {
				while (l < 2 * M && sig(ps[l].ang - ps[j].ang - PI / 2) < 0)
					l++;
				while (r < 2 * M && sig(ps[r].ang - ps[j].ang - PI) < 0)
					r++;
				ans -= r - l;
			}
			for (int j = 0; j < M && ps[j].ang < eps; j++) {
				int k = j;
				while (ps[k].ang < ps[j].ang + eps)
					k++;
				int tot = k - j;
				ans -= tot * (tot - 1) / 2;
				j = k - 1;
			}
		}
		cout << "There are ";
		cout << ans;
		cout << " sites for making valid tracks" << endl;
	}
	return 0;
}
