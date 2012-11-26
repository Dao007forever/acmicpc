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
struct Point
{
	int x, y, id;
}P[MAXN];
int N;

bool cmp(Point a, Point b)
{
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d%d", &P[i].x, &P[i].y);
		P[i].id = i + 1;
	}
	sort(P, P + N, cmp);
	for (int i = 0; i < N; i += 2)
	{
		printf("%d %d\n", P[i].id, P[i + 1].id);
	}
	return 0;
}
