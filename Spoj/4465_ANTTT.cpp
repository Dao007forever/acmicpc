#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1005;
const double eps = 1e-8;
struct Point {
	double x, y;
};
struct Line {
	Point A, B;
}p[maxn];
struct Union_Find{
	int rank[maxn], parent[maxn];

	Union_Find() {
		for (int i = 0; i < maxn; i++) {
			rank[i] = 0;
			parent[i] = i;
		} 
	}

	int Find(int x) {
		if (parent[x] == x) return x;
		return parent[x] = Find(parent[x]);
	}

	void Union(int x, int y) {
		x = Find(x);
		y = Find(y);

		if (x == y) return;
		
		if (rank[x] >= rank[y]) {
			parent[y] = x;
			if (rank[x] == rank[y])
				rank[x]++;
		}
		else {
			parent[x] = y;
		}
	}
}ant;
int n, m;

int dblcmp(double d) {
	return (d > eps) - (d < -eps);
}

double cross(Point a, Point b, Point c)
{
        return ((c.x - a.x) * (b.y - a.y) - (b.x - a.x) * (c.y - a.y));
}

int xyCmp(double p, double mini,double maxi)
{
        return dblcmp(p - mini) * dblcmp(p - maxi);
}

int betweenCmp(Point a, Point b, Point c)
{
        if (fabs(b.x - c.x) > fabs(b.y - c.y))
                return xyCmp(a.x, min(b.x, c.x), max(b.x, c.x));
        else return xyCmp(a.y, min(b.y, c.y), max(b.y, c.y));
}

int segcross(Point a, Point b, Point c, Point d)
{
        double s1, s2, s3, s4;
        int d1, d2, d3, d4;
        d1 = dblcmp(s1 = cross(a, b, c));
        d2 = dblcmp(s2 = cross(a, b, d));
        d3 = dblcmp(s3 = cross(c, d, a));
        d4 = dblcmp(s4 = cross(c, d, b));
        if ((d1 ^ d2) == -2 && (d3 ^ d4) == -2) return 1;
        
        if (d1 == 0 && betweenCmp(c, a, b) <= 0 ||
                d2 == 0 && betweenCmp(d, a, b) <= 0 ||
                d3 == 0 && betweenCmp(a, c, d) <= 0 ||
                d4 == 0 && betweenCmp(b, c, d) <= 0)
                return 1;
        return 0;
}

int main() {
	freopen("in.txt", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%lf%lf%lf%lf", &p[i].A.x, &p[i].A.y, &p[i].B.x, &p[i].B.y);
		Union_Find ant;
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++) {
				if (segcross(p[i].A, p[i].B, p[j].A, p[j].B)) {
					if (ant.Find(i) != ant.Find(j)) {
						ant.Union(i, j);
					}
				}
			}
		while (m--) {
			int x, y;
			scanf("%d%d", &x, &y);
			x--; y--;
			if (ant.Find(x) == ant.Find(y)) {
				printf("YES\n");
			} else {
				printf("NO\n");
			}
		}
	}
	return 0;
}
