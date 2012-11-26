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

struct Point {
	double x, y;

	Point(double _x = 0, double _y = 0): x(_x), y(_y) {}
	
	void input() {
		scanf("%lf%lf", &x, &y);
	}
	
	void output() {
		printf("%.12lf %.12lf\n", x, y);
	}
}ori[3], in[3], out[3];

Point operator + (const Point &p1, const Point &p2) {
	return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator - (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

Point operator * (const Point &p, double r) {
	return Point(p.x * r, p.y * r);
}

Point operator / (const Point &p, double r) {
	return Point(p.x / r, p.y / r);
}

int main() {
	for (int i = 0; i < 3; i++)
		ori[i].input();
	in[0] = (ori[0] + ori[1] + ori[2]) / 3;
	out[0] = in[0] + (ori[0] - in[0]) + (ori[1] - in[0]);
	out[1] = in[0] + (ori[1] - in[0]) + (ori[2] - in[0]);
	out[2] = in[0] + (ori[2] - in[0]) + (ori[0] - in[0]);
	in[1] = (in[0] * 2.0 + ori[0]) / 3.0;
	in[2] = (in[0] * 2.0 + out[0]) / 3.0;
	for (int i = 0; i < 3; i++)
		in[i].output();
	for (int i = 0; i < 3; i++)
		out[i].output();
	return 0;
}
