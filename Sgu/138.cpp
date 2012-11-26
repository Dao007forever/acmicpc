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
	int d, id;
}P[MAXN];
int N;
int ans[MAXN * MAXN][2];

bool cmp(Node a, Node b)
{
	return a.d > b.d;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	int sum = 0;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &P[i].d), P[i].id = i;
		sum += P[i].d;
	}
	sort(P + 1, P + N + 1, cmp);
	sum /= 2;
	printf("%d\n", sum);
	int tot = 0;
	for (int i = 1; i <= N; i++)
	{
		while (tot < sum && P[i].d > 1)
		{
			P[i].d--;
			tot++;
			ans[tot][0] = P[i].id;
		}
		if (tot < sum)
		{
			tot++;
			ans[tot][1] = P[i].id;
			ans[tot][0] = P[i + 1].id;
			P[i + 1].d--;
			P[i].d--;
		}
	}
	int top = 1;
	while (P[top].d == 0)
		top++;
	for (int i = 1; i <= sum; i++)
	{
		printf("%d ", ans[i][0]);
		if (ans[i][1]) printf("%d", ans[i][1]);
		else 
		{
			printf("%d", P[top].id);
			P[top].d--;
			while (P[top].d == 0) top++;
		}
		printf("\n");
	}
	return 0;
}
