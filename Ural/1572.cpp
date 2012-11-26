/*
 * 模拟
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

const int MAXN = 200 + 10;
int type, size, N, sum;

void circle(int ty, double ts)
{
	if (ty == 1)
	{
		if (ts <= size) sum++;
	}
	else if (ty == 2)
	{
		if (ts <= 2 * size) sum++;
	}
	else
	{
		double tmp = ts * sqrt(3.0) / 2.0;
		if (tmp <= 2 * size) sum++;
	}
}

void square(int ty, double ts)
{
	double tsize = size * sqrt(2.0);
	if (ty == 2)
	{
		if (ts <= tsize) sum++;
	}
	else if (ty == 1)
	{
		if (2 * ts <= tsize) sum++;
	}
	else
	{
		double tmp = ts * sqrt(3.0) / 2.0;
		if (tmp <= tsize) sum++;
	}
}

void triangle(int ty, double ts)
{
	if (ty == 2)
	{
		if (ts <= size) sum++;
	}
	else if (ty == 1)
	{
		if (2 * ts <= size) sum++;
	}
	else
	{
		double tmp = ts * sqrt(3.0) / 2.0;
		if (tmp <= size) sum++;
	}
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &type, &size);
	scanf("%d", &N);
	int t;
	double s;
	sum = 0;
	if (type == 1)
	{
		for (int i = 0; i < N; i++)
		{
			scanf("%d%lf", &t, &s);
			circle(t, s);
		}
	}
	else if (type == 2)
	{
		for (int i = 0; i < N; i++)
		{
			scanf("%d%lf", &t, &s);
			square(t, s);
		}
	}
	else
	{
		for (int i = 0; i < N; i++)
		{
			scanf("%d%lf", &t, &s);
			triangle(t, s);
		}
	}
	printf("%d\n", sum);
	return 0;
}
