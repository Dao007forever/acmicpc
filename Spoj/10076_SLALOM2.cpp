/*
 * Author:  Yang Zhang
 * Created Time:  2012/8/20 21:11:59
 * File Name: 10076_SLALOM2.cpp
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

const double eps = 1e-9, inf = 1e300;
int n;
double dp[1005][2];
struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
}interv[1005][2];
int sig(double d) {
    return (d > eps) - (d < -eps);
}
double cross(Point o, Point a, Point b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
Point intersect(Point a, Point b, double y) {
    double dx = b.x - a.x, dy = b.y - a.y;
    return Point(a.x + dx / dy * (y - a.y), y);
}
double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) && n) {
        Point p, e[2];
        scanf("%lf%lf", &p.x, &p.y);
        interv[0][0] = interv[0][1] = p;
        for (int i = 1; i <= n; i++) {
            double y, X1, X2;
            scanf("%lf%lf%lf", &y, &X1, &X2);
            interv[i][0] = Point(X1, y);
            interv[i][1] = Point(X2, y);
        }
        dp[n][0] = dp[n][1] = 0;
        for (int i = n - 1; i >= 0; i--) {
            for (int side = 0; side < 2; side++) {
                Point p(interv[i][side]);
                e[0] = interv[i + 1][0]; e[1] = interv[i + 1][1];

                int j;
                dp[i][side] = inf;
                for (j = i + 1; j <= n; j++) {
                    if (sig(cross(p, interv[j][1], e[0])) > 0 || sig(cross(p, e[1], interv[j][0])) > 0) {
                        break;
                    } else {
                        if (sig(cross(p, e[0], interv[j][0])) >= 0) {
                            e[0] = interv[j][0];
                            dp[i][side] = min(dp[i][side], dist(p, interv[j][0]) + dp[j][0]);
                        }
                        if (sig(cross(p, interv[j][1], e[1])) >= 0) {
                            e[1] = interv[j][1];
                            dp[i][side] = min(dp[i][side], dist(p, interv[j][1]) + dp[j][1]);
                        }
                    }
                }
                if (j > n) {
                    e[0] = intersect(p, e[0], interv[n][0].y);
                    e[1] = intersect(p, e[1], interv[n][0].y);
                    
                    double d;
                    if (p.x > e[1].x) d = dist(p, e[1]);
                    else if (p.x < e[0].x) d = dist(p, e[0]);
                    else d = p.y - e[0].y;
                    dp[i][side] = min(dp[i][side], d);
                }
                if (i == 0) break;
            }
        }
        printf("%.11f\n", dp[0][0]);
    }
    return 0;
}

