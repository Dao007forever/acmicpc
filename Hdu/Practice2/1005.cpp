#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 300 + 10;
const double eps = 1e-8;
struct Point
{
	double x, y;
}seg[MAXN][2], p[2 * MAXN];
int T, N, num, flag;

int Check(double d)
{
	if (d > eps) return 1;
	else if (d < -eps) return -1;
	return 0;
}
double dist(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
double cross(Point a, Point b, Point c)
{
	return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++)
	{
		num = 0;
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
		{
			scanf("%lf%lf%lf%lf", &seg[i][0].x, &seg[i][0].y, &seg[i][1].x, &seg[i][1].y);
			p[++num] = seg[i][0];
			p[++num] = seg[i][1];
		}
		flag = 0;
		bool diff = 0;
		for (int i = 1; i < num; i++)
		if (Check(p[i].x - p[i + 1].x) != 0 && Check(p[i].y - p[i + 1].y) != 0)
		{
			diff = 1;
			break;
		}

		for (int i = 1; i < num; i++)
		{
			for (int j = i + 1; j <= num; j++)
			{
				if (Check(dist(p[i], p[j])) == 0) continue;
				flag = 1;
				for (int k = 1; k <= N; k++)
				if (Check(cross(p[i], p[j], seg[k][0])) * Check(cross(p[i], p[j], seg[k][1])) > 0)
				{
					flag = 0;
					break;
				}
				if (flag) break;
			}
			if (flag) break;
		}
		if (!diff || flag) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
