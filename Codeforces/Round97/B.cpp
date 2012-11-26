#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
struct Point {
	int x, y;
}ps[10];
int a[11];
int n = 8;

int sig(double d) {
	return (d > eps) - (d < -eps);
}

double dist(Point a, Point b) {
	double dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

long long dot(Point o, Point a, Point b) {
	return (long long)(a.x - o.x) * (b.x - o.x) + (long long)(a.y - o.y) * (b.y - o.y);
}

bool isRec(int a, int b, int c, int d) {
	Point A = ps[a], B = ps[b], C = ps[c], D = ps[d];
	double d1 = dist(A, B), d2 = dist(A, C), d3 = dist(A, D);
	int Max = b;
	double dmax = d1;
	if (sig(d2 - dmax) > 0) {
		dmax = d2;
		Max = c;
	}
	if (sig(d3 - dmax) > 0) {
		dmax = d3;
		Max = d;
	}
	if (Max == b) {
		int tmp = c;
		c = b;
		b = tmp;
	}else if (Max == d) {
		int tmp = c;
		c = d;
		d = tmp;
	}
	A = ps[a], B = ps[b], C = ps[c], D = ps[d];
	d1 = dist(A, B), d2 = dist(A, C), d3 = dist(A, D);
	if (dot(A, B, D) == 0 && dot(C, B, D) == 0 && dot(B, A, C) == 0) return true;
	return false;
}

bool isSquare(int a, int b, int c, int d) {
	Point A = ps[a], B = ps[b], C = ps[c], D = ps[d];
	double d1 = dist(A, B), d2 = dist(A, C), d3 = dist(A, D);
	int Max = b;
	double dmax = d1;
	if (sig(d2 - dmax) > 0) {
		dmax = d2;
		Max = c;
	}
	if (sig(d3 - dmax) > 0) {
		dmax = d3;
		Max = d;
	}
	if (Max == b) {
		int tmp = c;
		c = b;
		b = tmp;
	}else if (Max == d) {
		int tmp = c;
		c = d;
		d = tmp;
	}
	A = ps[a], B = ps[b], C = ps[c], D = ps[d];
	d1 = dist(A, B), d2 = dist(A, C), d3 = dist(A, D);
	if (sig(d1 - d3) != 0) return false;
	if (dot(A, B, D) == 0 && dot(C, B, D) == 0 && dot(B, A, C) == 0) return true;
	return false;
}

int main() {
//	freopen("in", "r", stdin);
	for (int i = 1; i <= n; i++) {
		a[i - 1] = i;
		scanf("%d%d", &ps[i].x, &ps[i].y);
	}
	do {
		if (isSquare(a[0], a[1], a[2], a[3]) && isRec(a[4], a[5], a[6], a[7]))
		{
			printf("YES\n");
			printf("%d %d %d %d\n", a[0], a[1], a[2], a[3]);
			printf("%d %d %d %d\n", a[4], a[5], a[6], a[7]);
			return 0;
		}
	}while (next_permutation(a, a + n));
	printf("NO\n");
	return 0;
}
