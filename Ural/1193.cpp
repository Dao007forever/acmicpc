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
struct Node
{
	int a, b, c;
}P[MAXN];
int N;

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d%d%d", &P[i].a, &P[i].b, &P[i].c);
	for (int i = 1; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
		if (P[j].a < P[i].a)
		{
			swap(P[i], P[j]);
		}
	int now = P[1].a, res = 0;
	for (int i = 1; i <= N; i++)
	{
		if (P[i].a > now) now = P[i].a;
		now += P[i].b;
		res = max(res, now - P[i].c);
	}
	printf("%d\n", res);
	return 0;
}
