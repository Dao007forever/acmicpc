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

const int MAXN = 10000 + 10;
struct Line
{
	int x1, y1, x2, y2;
};
Line P[MAXN];
int N;

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d%d%d%d", &P[i].x1, &P[i].y1, &P[i].x2, &P[i].y2);
		if (P[i].x1 > P[i].x2) swap(P[i].x1, P[i].x2);
		if (P[i].y1 > P[i].y2) swap(P[i].y1, P[i].y2);
	}
	int x0, y0;
	scanf("%d%d", &x0, &y0);
	int cnt = 0;
	for (int i = 1; i <= N; i++)
	{
		if (P[i].x1 == P[i].x2)
		{
			if (x0 == P[i].x1 && P[i].y1 <= y0 && y0 <= P[i].y2)
			{
				printf("BORDER\n");
				return 0;
			}
		}
		if (P[i].y1 == P[i].y2)
		{
			if (y0 == P[i].y1 && P[i].x1 <= x0 && x0 <= P[i].x2)
			{
				printf("BORDER\n");
				return 0;
			}
			if (P[i].y1 > y0 && P[i].x1 < x0 && x0 <= P[i].x2) cnt++;
		}
	}
	if (cnt & 1) printf("INSIDE\n");
	else printf("OUTSIDE\n");
	return 0;
}
