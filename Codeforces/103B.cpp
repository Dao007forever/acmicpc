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
int N, M;
int p[MAXN];

int getfather(int x)
{
	if (p[x] != x)
		p[x] = getfather(p[x]);
	return p[x];
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &N, &M);
	if (N < 3)
	{
		printf("NO\n");
		return 0;
	}
	for (int i = 1; i <= N; i++)
		p[i] = i;
	for (int i = 1; i <= M; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		int pu = getfather(u), pv = getfather(v);
		if (pu != pv)
			p[pu] = pv;
	}
	int root = getfather(1);
	for (int i = 1; i <= N; i++)
	if (getfather(i) != root)
	{
		printf("NO\n");
		return 0;
	}
	if (N == M) printf("FHTAGN!\n");
	else printf("NO\n");
	return 0;
}
