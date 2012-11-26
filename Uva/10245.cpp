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
}P[MAXN];
int N;
int idx[MAXN], idy[MAXN];

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double dist(int i, int j)
{
    Point a = P[i], b = P[j];
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool cmpx(int i, int j)
{
    return P[i].x < P[j].x;
}

bool cmpy(int i, int j)
{
    return P[i].y < P[j].y;
}

double closest(int l, int r)
{
    if (l + 1 == r) return dist(idx[l], idx[r]);
    if (l + 2 == r) 
        return min(dist(idx[l], idx[l + 1]), min(dist(idx[l + 1], idx[r]), dist(idx[l], idx[r])));
    int Mid = (l + r) / 2;
    double ans = min(closest(l, Mid), closest(Mid + 1, r));

    int cnt = 0;
    for (int i = l; i <= r; i++)
    if (P[idx[i]].x >= P[idx[Mid]].x - ans && P[idx[i]].x <= P[idx[Mid]].x + ans)
        idy[cnt++] = idx[i];

    sort(idy, idy + cnt, cmpy);
    for (int i = 0; i < cnt; i++)
        for (int j = i + 1; j < cnt; j++)
        {
            if (P[idy[j]].y - P[idy[i]].y >= ans) break;
            ans = min(ans, dist(idy[i], idy[j]));
        }
    return ans;
}

int main()
{
    freopen("a", "r", stdin);
    while (scanf("%d", &N) && N)
    {
        for (int i = 0; i < N; i++)
        {
            scanf("%lf%lf", &P[i].x, &P[i].y);
            idx[i] = i;
        }
		if (N == 1)
		{
			printf("INFINITY\n");
			continue;
		}
        sort(idx, idx + N, cmpx);
        double dis = closest(0, N - 1);
		if (dblcmp(dis - 10000.0) >= 0) printf("INFINITY\n");
		else printf("%.4lf\n", dis);
    }
    return 0;
}
