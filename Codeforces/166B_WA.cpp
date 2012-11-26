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

#define MAXN 300005
const double eps = 1e-8;
struct Point {
	double x, y;
}P[MAXN];
int N;

int dblcmp(double d) {
	return (d > eps) - (d < -eps);
}

double cross_product(Point o, Point a, Point b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

int xyCmp(double p, double mini, double maxi)
{
    return dblcmp(p - mini) * dblcmp(p - maxi);
}

int betweenCmp(Point a, Point b, Point c)
{
    if (fabs(b.x - c.x) > fabs(b.y - c.y))
        return xyCmp(a.x, min(b.x, c.x), max(b.x, c.x));
    else return xyCmp(a.y, min(b.y, c.y), max(b.y, c.y));
}

//A是要判断的点,P[1..N]是凸多边形,P[N+1]=P[1]且P[]为逆时针，若为顺时针，则要改两个地方：
//if (dblcmp(cross_product(P[1], A, P[Mid])) >= 0) Left = Mid + 1;
//if (tmp < 0) return true;

bool isinPolygon(Point A)
{
    int Left = 2, Right = N + 1, ret;
    while (Left <= Right)
    {
        int Mid = (Left + Right) >> 1;
        if (dblcmp(cross_product(P[1], A, P[Mid])) <= 0) {
			ret = Mid;
			Left = Mid + 1;
		}
        else Right = Mid - 1;
    }
    int tmp = dblcmp(cross_product(P[ret - 1], P[ret], A));
    if (tmp > 0) return true;//Inside the polygon
    //if (tmp == 0 && betweenCmp(A, P[ret - 1], P[ret]) <= 0) return true;//On the edge of the polygon

    return false;
}

int main() {
	freopen("in", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%lf%lf", &P[i].x, &P[i].y);
	}
	reverse(P + 1, P + N + 1);
	P[N + 1] = P[1];
	bool flag = true;
	int m;
	scanf("%d", &m);
	while (m--) {
		Point tmp;
		scanf("%lf%lf", &tmp.x, &tmp.y);
		if (!isinPolygon(tmp)) flag = false;
	}
	if (flag) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
