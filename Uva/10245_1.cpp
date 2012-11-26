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

const int MAXN = 11111;
const double eps = 1e-8;
struct Point
{
	double x, y;
}p[MAXN];
struct Segment
{
	Point a, b;
	void init(Point x, Point y)
	{
		a = x;
		b = y;
	}
};
int N;

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

bool cmp(Point a, Point b)
{
	return a.x < b.x;
}

double dist(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double closest_pair()
{
    sort(p, p + N, cmp); // 依X座標排序
 
    double ans = 1e9;     // 最近點對的距離
    Segment cp[MAXN];     // 最近點對
    int n = 0;          // 最近點對的數目
 
    for (int i = 0; i < N; i++)
        for (int j = i + 1; j < N; j++)
        {
            if (p[i].x + ans < p[j].x) break;
            double dij = dist(p[i], p[j]);
            if (dblcmp(dij - ans) < 0)
			{
                ans = dij;
				n = 0;
				cp[n++].init(p[i], p[j]);
			}
            else if (dblcmp(ans - dij) == 0)
                cp[n++].init(p[i], p[j]);
        }
 
    return ans;
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) && N)
	{
		for (int i = 0; i < N; i++)
			scanf("%lf%lf", &p[i].x, &p[i].y);
		double dis = closest_pair();
		if (dblcmp(dis - 10000.0) >= 0) printf("INFINITY\n");
		else printf("%.4lf\n", dis);
	}
	return 0;
}
