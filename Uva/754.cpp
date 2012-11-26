#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#define eps 1.0e-8

const int MAXN = 3000;
struct Point
{
	double x, y;
};
int N;
Point line[MAXN][2];

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double det(double x1, double y1, double x2, double y2)
{
	return x1 * y2 - x2 * y1;
}

double cross(Point a, Point b, Point c)
{
	return det(b.x - a.x, b.y - a.y, c.x - a.x, c.y - a.y);
}

int segcrossSimple(Point a, Point b, Point c, Point d)
{
	return (dblcmp(cross(a, c, d)) ^ dblcmp(cross(b, c, d))) == -2 && (dblcmp(cross(c, a, b)) ^ dblcmp(cross(d, a, b))) == -2;
}

int tot;
Point res[2 * MAXN];

int main()
{
	freopen("a", "r", stdin);

	int T;
	scanf("%d", &T);
	while (T--)
	{
		memset(line, 0, sizeof(line));
		memset(res, 0, sizeof(res));
		tot = 0;
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
		{
			scanf("%lf%lf%lf%lf", &line[i][0].x, &line[i][0].y, &line[i][1].x, &line[i][1].y);
			if (dblcmp(line[i][0].x) == 0 || dblcmp(line[i][0].x - 100) == 0 || dblcmp(line[i][0].y) == 0 || dblcmp(line[i][0].y - 100) == 0)
			{
				res[++tot] = line[i][0];
			}
			if (dblcmp(line[i][1].x) == 0 || dblcmp(line[i][1].x - 100) == 0 || dblcmp(line[i][1].y) == 0 || dblcmp(line[i][1].y - 100) == 0)
			{
				res[++tot] = line[i][1];
			}
		}
		Point p;
		scanf("%lf%lf", &p.x, &p.y);
		int ans = MAXN;
		for (int i = 1; i <= tot; i++)
		{
			int num = 0;
			for (int j = 1; j <= N; j++)
			{
				if (segcrossSimple(p, res[i], line[j][0], line[j][1]))
					num++;
			}
			if (num < ans) ans = num;
		}
		if (N == 0) printf("Number of doors = 1\n");
		else printf("Number of doors = %d\n", ans + 1);
		if (T) printf("\n");
	}
	return 0;
}
