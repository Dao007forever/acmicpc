/*
 * Author: Yang Zhang
 * Created Time: Wed 05 Sep 2012 01:13:37 PM CST
 * File Name: 8282_DIST.cpp
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

const int MAXN = 100005;
const double eps = 1e-6;
int n;
vector<int> x, y, p;
int id[MAXN];
LL A, B, C, D;

double Calc(double z) {
	return A*z*z*z+B*z*z+C*z+D;
}

void update(double l, double r, double &ret) {
	double a = 3.0 * A, b = 2.0 * B, c = C;
	if (a == 0) {
		if (b != 0) {
			double ans = -c / b;
			if (l <= ans && ans <= r)
				ret = min(ret, Calc(ans));
		}
		return;
	}
	double delta = b*b-4*a*c;
	if (delta >= 0) {
		double x1 = (-b+sqrt(delta)) / (2.0*a);
		double x2 = (-b-sqrt(delta)) / (2.0*a);
		if (l <= x1 && x1 <= r) ret = min(ret, Calc(x1));
		if (l <= x2 && x2 <= r) ret = min(ret, Calc(x2));
	}
}


double solve(const vector<int> &a) {
	double ret = 1e90;
	A = 0, B = 0, C = 0, D = 0;
	for (int i = 0; i < n; i++) {
		if (p[ id[i] ] == 0) {
			D += 1;
		} else if (p[ id[i] ] == 1) {
			D += 1 * a[ id[i] ];
			C += -1;
		} else if (p[ id[i] ] == 2) {
			D += 1 * a[ id[i] ] * a[ id[i] ];
			C += -2 * a[ id[i] ];
			B += 1;
		} else {
			D += 1 * a[ id[i] ] * a[ id[i] ] * a[ id[i] ];
			C += -3 * a[ id[i] ] * a[ id[i] ];
			B += 3 * a[ id[i] ];
			A += -1;
		}
	}

	update(-1e90, a[ id[0] ], ret);
	ret = min(ret, Calc(a[ id[0] ]));

	for (int i = 0; i < n; i++) {
		if (p[ id[i] ] == 1) {
			D += -2 * a[ id[i] ];
			C += 2;
		} else if (p[ id[i] ] == 3) {
			D += -2 * a[ id[i] ] * a[ id[i] ] * a[ id[i] ];
			C += 6 * a[ id[i] ] * a[ id[i] ];
			B += -6 * a[ id[i] ];
			A += 2;
		}
		update(a[ id[i] ], a[ id[i + 1] ], ret);
		ret = min(ret, Calc(a[ id[i] ]));
		ret = min(ret, Calc(a[ id[i + 1] ]));
	}
	
	return ret;
}

bool cmpx(int i, int j) {
	return x[i] < x[j];
}

bool cmpy(int i, int j) {
	return y[i] < y[j];
}

int main() {
	int Test;
	scanf("%d", &Test);
	for (; Test--; ) {
		x.clear(); y.clear(); p.clear();
		memset(id, 0, sizeof(id));
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			x.PB(a); y.PB(b); p.PB(c);
			id[i] = i;
		}
		x.PB(5000); y.PB(5000); id[n] = n;
		sort(id, id + n + 1, cmpx);
		double ansx = solve(x);

		sort(id, id + n + 1, cmpy);
		double ansy = solve(y);
		printf("%.3f\n", ansx + ansy);
	}
	return 0;
}

