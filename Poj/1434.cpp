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

const int MAXN = 50000 + 10;
const double eps = 1e-3;
int N;
struct BOX
{
	int b, h, w, d, f;
}P[MAXN];
int Vol, total;
double Left, Right;

void init()
{
	total = 0;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d%d%d%d", &P[i].b, &P[i].h, &P[i].w, &P[i].d);
		P[i].f = P[i].b + P[i].h;
		total += P[i].h * P[i].w * P[i].d;
		if (P[i].f > Right) Right = P[i].f;
		if (P[i].b < Left) Left = P[i].b;
	}
	scanf("%d", &Vol);
}

double calc(double line)
{
	double res = 0;
	for (int i = 1; i <= N; i++)
	{
		double tmp = min(line, (double)P[i].f);
		if (tmp > P[i].b) 
			res += (tmp - P[i].b) * P[i].w * P[i].d;
	}
	return res;
}

void solve()
{
	while (Right - Left > eps)
	{
		double Mid = (Left + Right) / 2.0;
		double ans = calc(Mid);
		if (ans >= Vol) Right = Mid;
		else Left = Mid;
	}
	printf("%.2lf\n", Left);
}

int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		Left = 99999999, Right = 0;
		init();
		if (Vol > total)
		{
			printf("OVERFLOW\n");
			continue;
		}
		solve();
	}
	return 0;
}
