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

const int MAXN = 1000 + 10;
struct Product
{
	char type[100];
	int price, quality;
}P[MAXN];
int N, budget, K;
int f[MAXN];

bool cmp(Product a, Product b)
{
	if (strcmp(a.type, b.type) == 0)
		return a.quality < b.quality;
	return (strcmp(a.type, b.type) < 0);
}

bool Check(int limit)
{
	int sum = 0;
	for (int i = 1; i <= K; i++)
	{
		int Min = 2147483647;
		for (int j = f[i - 1] + 1; j <= f[i]; j++)
			if (P[j].quality >= limit)
				if (P[j].price < Min) Min = P[j].price;
		if (Min == 2147483647) return 0;
		sum += Min;
	}
	if (sum > budget) return 0;
	return 1;
}

int main()
{
	freopen("in", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &N, &budget);
		int Right = 0, Left = 2147483647;
		for (int i = 1; i <= N; i++)
		{
			char name[100];
			scanf("%s%s%d%d", P[i].type, name, &P[i].price, &P[i].quality);
			if (P[i].quality < Left) Left = P[i].quality;
			if (P[i].quality > Right) Right = P[i].quality;
		}
		sort(P + 1, P + N + 1, cmp);

		memset(f, 0, sizeof(f));
		K = 0;
		f[0] = 0;
		for (int i = 1; i < N; i++)
		{
			if (strcmp(P[i].type, P[i + 1].type) != 0)
				f[++K] = i;
		}
		f[++K] = N;

		bool flag = false;
		while (Left <= Right)
		{
			int Mid = (Left + Right) / 2;
			if (Check(Mid))
			{
				Left = Mid + 1;
				flag = true;
			}
			else Right = Mid - 1;
		}
		if (flag) printf("%d\n", Right);
		else printf("0\n");
	}
	return 0;
}
