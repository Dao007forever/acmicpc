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

const int MAXN = 100 + 10;
const double eps = 1e-6;
int N, Vb, Vs;
int X[MAXN], s[MAXN];
int Xu, Yu;

double dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double dist(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d%d", &N, &Vb, &Vs);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &X[i]);
		if (i > 1) s[i] = s[i - 1] + (int)fabs(X[i] - X[i - 1]);
	}
	scanf("%d%d", &Xu, &Yu);

	int ans = 1;
	double Min = 1e10;
	for (int i = 2; i <= N; i++)
	{
		double t1 = (double)s[i] / Vb;
		double t2 = dist((double)X[i], 0.0, (double)Xu, (double)Yu) / Vs;
		if (dblcmp(t1 + t2 - Min) <= 0)
		{
			Min = t1 + t2;
			ans = i;
		}
	}
	printf("%d\n", ans);
	return 0;
}
