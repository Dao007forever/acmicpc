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
char str[MAXN];
int num[MAXN];

int main()
{
//	freopen("a", "r", stdin);
	while (scanf("%s", str) != EOF)
	{
		if (strcmp(str, "1") == 0)
		{
			printf("1\n");
			continue;
		}
		memset(num, 0, sizeof(num));
		int n = strlen(str);
		for (int i = 1; i <= n; i++)
			num[i] = str[i - 1] - '0';

		for (int i = 1; i <= n; i++)
			num[i] *= 2;
		for (int i = n; i >= 1; i--)
		{
			if (num[i] >= 10)
			{
				num[i] -= 10;
				num[i - 1]++;
			}
		}

		if (num[n] >= 2)
		{
			num[n] -= 2;
		}
		else
		{
			int i = n;
			num[i] -= 2;
			while (num[i] < 0)
			{
				num[i] += 10;
				num[i - 1]--;
				i--;
			}
		}
		if (num[0])
		{
			for (int i = 0; i <= n; i++)
				printf("%d", num[i]);
			printf("\n");
		}
		else
		{
			for (int i = 1; i <= n; i++)
				printf("%d", num[i]);
			printf("\n");
		}
	}
	return 0;
}
