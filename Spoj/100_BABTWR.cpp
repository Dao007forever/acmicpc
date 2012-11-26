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

const int MAXN = 50;
struct Box
{
	int x, y, z;
};
Box B[3 * MAXN];
int F[3 * MAXN];
int N;

int DP(int u)
{
	if (F[u] != -1) return F[u];
	int Max = 0;
	for (int i = 0; i < 3 * N; i++)
	if ((B[u].x > B[i].x && B[u].y > B[i].y) || (B[u].x > B[i].y && B[u].y > B[i].x))
	{
		int tmp = DP(i);
		if (tmp > Max) Max = tmp;
	}
	F[u] = Max + B[u].z;
	return F[u];
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) && N)
	{
		for (int i = 0; i < 3 * N; i++)
			F[i] = -1;
		for (int i = 0; i < N; i++)
		{
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			B[3 * i].x = x, B[3 * i].y = y, B[3 * i].z = z;
			B[3 * i + 1].x = x, B[3 * i + 1].y = z, B[3 * i + 1].z = y;
			B[3 * i + 2].x = z, B[3 * i + 2].y = y, B[3 * i + 2].z = x;
		}
		int ans = 0;
		for (int i = 0; i < 3 * N; i++)
		{
			int temp = DP(i);
			if (temp > ans) ans = temp;
		}
		printf("%d\n", ans);
	}
	return 0;
}
