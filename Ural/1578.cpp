/*
 * 调整，每次枚举相邻的三个点ps[i-1],ps[i],ps[i+1]，如果它们的夹角是钝角，就交换i和i+1，直到满足条件为止
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

const double eps = 1e-8;
struct Point {
	double x, y;

	void input() {
		scanf("%lf%lf", &x, &y);
	}
}ps[2222];
int q[2222];

int sig(double d) {
	return (d > eps) - (d < -eps);
}

double dot(Point o, Point a, Point b) {
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}

int check(Point a, Point o, Point b) {
	double tmp = dot(o, a, b);
	return sig(tmp);
}

int main() {
	freopen("in", "r", stdin);
	int n;
	cin >> n;
	n += 2;
	for (int i = 0; i < n; i++) {
		ps[i].input();
		q[i] = i;
	}
	bool flag = true;
	while (flag) {
		flag = false;
		for (int i = 1; i < n - 1; i++) {
			if (check(ps[q[i - 1]], ps[q[i]], ps[q[i + 1]]) <= 0) {
				flag = true;
				swap(q[i], q[i + 1]);
			}
		}
	}
	puts("YES");
	for (int i = 0; i < n; i++)
		printf("%d%c", q[i] + 1, i == n - 1 ? '\n' : ' ');
	return 0;
}
