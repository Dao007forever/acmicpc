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
int sig(double d) {
	return (d > eps) - (d < -eps);
}
struct Point {
	double x, y;

	void input() {
		cin >> x >> y;
	}

	void output() {
		printf("%.0f %.0f\n", x, y);
	}

}ps[333];
int n;
int adj[333][333];

double cross(Point o, Point a, Point b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

double dot(Point o, Point a, Point b) {
	return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}

double dist(Point a, Point b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool onSeg(Point p, Point a, Point b) {
	return sig(cross(p, a, b)) == 0 && sig(dot(p, a, b)) <= 0;
}

int main() {
	freopen("in", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++)
		ps[i].input();

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) {
			for (int k = 0; k < n; k++)
				if (i != k && j != k) 
					if (onSeg(ps[k], ps[i], ps[j])) {
						adj[i][k] = adj[k][i] = 1;
						adj[k][j] = adj[j][k] = 1;
					}
		}
	double ret = 0.0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (!adj[i][j]) {
				ret += dist(ps[i], ps[j]);
				//cout << i << " " << j << endl;
			}
	printf("%.0f\n", ret);
	return 0;
}
