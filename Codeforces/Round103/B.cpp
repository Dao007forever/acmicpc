#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

struct Circle {
	int x, y, r;
}c[1111];
int n;
int xa, xb, ya, yb;

bool inside(Circle c, int x, int y) {
	if (c.r * c.r >= (c.x - x) * (c.x - x) + (c.y - y) * (c.y - y)) return true;
	return false;
}

bool check(int x, int y) {
	for (int i = 0; i < n; i++)
		if (inside(c[i], x, y)) return false;
	return true;
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d%d%d%d", &xa, &ya, &xb, &yb);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &c[i].x, &c[i].y, &c[i].r);
	}
	int ret = 0;
	int maxx = max(xa, xb), minx = min(xa, xb);
	int maxy = max(ya, yb), miny = min(ya, yb);
	for (int i = miny + 1; i < maxy; i++) {
		if (check(minx, i)) ret++;
		if (check(maxx, i)) ret++;
	}
	for (int i = minx + 1; i < maxx; i++) {
		if (check(i, miny)) ret++;
		if (check(i, maxy)) ret++;
	}
	if (check(minx, miny)) ret++;
	if (check(minx, maxy)) ret++;
	if (check(maxx, miny)) ret++;
	if (check(maxx, maxy)) ret++;
	printf("%d\n", ret);
	return 0;
}
