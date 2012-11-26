/*
 * Author:  Yang Zhang
 * Created Time:  2012/8/20 19:48:28
 * File Name: 10070_TRICKTRT.cpp
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

#define maxn 50005
const double eps = 1e-6;
int n;
double x[maxn], y[maxn];

int sig(double d) {
    return (d > eps) - (d < -eps);
}

double dist(double X1, double Y1, double X2, double Y2) {
    return sqrt((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2));
}

double calc(double pos) {
    double Max = 0.0;
    for (int i = 0; i < n; i++) {
        double tmp = dist(x[i], y[i], pos, 0.0);
        if (sig(tmp - Max) >= 0) Max = tmp;
    }
    return Max;
}

int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) && n) {
        double l = 200000.0, r = -200000.0;
        for (int i = 0; i < n; i++) {
            scanf("%lf%lf", &x[i], &y[i]);
            l = min(l, x[i]);
            r = max(r, x[i]);
        }
        while (r - l > eps) {
            double mid1 = (l + r) / 2;
            double mid2 = (mid1 + r) / 2;
            double val1 = calc(mid1);
            double val2 = calc(mid2);
            if (val1 <= val2) r = mid2;
            else l = mid1;
        }
        double ret = calc(r);
        printf("%.9f %.9f\n", r, ret);
    }
    return 0;
}
