/*
 * Author: Yang Zhang
 * Created Time: Mon 27 Aug 2012 11:00:18 AM CST
 * File Name: 5159_IEXPOLRE.cpp
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

#define MAXN 200005
const double eps = 1e-8;
inline int sig(double d) {
	return (d > eps) - (d < -eps);
}
struct Point {
	double x, y;
}ps[MAXN], qs[MAXN];
struct Edge {
	int u, v;
	double w;
}edge[MAXN];
int n, m, E;
double Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
int p[MAXN];

inline int find(int x) {
	if (p[x] == x) return x;
	return p[x] = find(p[x]);
}

inline double dist(const Point &a, const Point &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
inline bool cmp1(const Edge &a, const Edge &b) {
	return a.w < b.w;
}
inline bool cmp2(const Point &a, const Point &b) {
	return (a.x + eps < b.x) || (a.x - eps <= b.x && a.y < b.y);
}
int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case #%d: ", cas);
		E = 0;
		scanf("%d%d", &n, &m);
		scanf("%lf%lf%lf%lf", &Ax, &Ay, &Bx, &By);
		scanf("%lf%lf%lf%lf", &Cx, &Cy, &Dx, &Dy);
		for (int i = 0; i < n; i++) {
			double t; scanf("%lf", &t);
			ps[i].x = Ax * t + Bx * (1 - t);
			ps[i].y = Ay * t + By * (1 - t);
		}
		sort(ps, ps + n, cmp2);
		int nn = n; n = !n ? 0 : 1;
		for (int i = 1; i < nn; i++)
			if (dist(ps[i], ps[i - 1]) > eps)
				ps[n++] = ps[i];
		for (int i = 1; i < n; i++) {
			edge[E].u = i - 1; edge[E].v = i;
			edge[E].w = dist(ps[i - 1], ps[i]);
			E++;
		}

		for (int i = 0; i < m; i++) {
			double t; scanf("%lf", &t);
			qs[i].x = Cx * t + Dx * (1 - t);
			qs[i].y = Cy * t + Dy * (1 - t);
		}
		sort(qs, qs + m, cmp2);
		int mm = m; m = !m ? 0 : 1;
		for (int i = 1; i < mm; i++)
			if (dist(qs[i], qs[i - 1]) > eps)
				qs[m++] = qs[i];
		for (int i = 1; i < m; i++) {
			edge[E].u = n + i - 1, edge[E].v = n + i;
			edge[E].w = dist(qs[i - 1], qs[i]);
			E++;
		}
		for (int i = 0; i < n; i++) {
			int l = 0, r = m - 1;
			while (r - l > 3) {
				int mid1 = (l + r) >> 1;
				int mid2 = (mid1 + r) >> 1;
				double d1 = dist(ps[i], qs[mid1]);
				double d2 = dist(ps[i], qs[mid2]);
				if (d1 < d2) r = mid2;
				else l = mid1;
			}
			for (int j = l; j <= r; j++) {
				edge[E].u = i; edge[E].v = n + j; edge[E].w = dist(ps[i], qs[j]);
				E++;
			}
		}
		sort(edge, edge + E, cmp1);
		for (int i = 0; i < n + m; i++) p[i] = i;
		double ret = 0;
		for (int i = 0; i < E; i++) {
			int u = find(edge[i].u), v = find(edge[i].v);
			if (u != v) {
				ret += sqrt(edge[i].w);
				p[u] = v;
			}
		}
		printf("%.3f\n", ret);
	}
	return 0;
}

