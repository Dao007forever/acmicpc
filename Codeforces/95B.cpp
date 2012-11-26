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

const int MAXN = 200000 + 10;
char st[MAXN];
int res[MAXN], a[MAXN];
int n;

int main()
{
	freopen("a", "r", stdin);
	scanf("%s", st + 1);
	n = strlen(st + 1);
	for (int i = n; i; i--)
	if (st[i] < '4') a[i] = 0;
	else if (st[i] == '4') a[i] = min(1, a[i + 1]);
	else if (st[i] < '7') a[i] = 1;
	else if (st[i] == '7') a[i] = a[i + 1] + 1;
	else a[i] = 1000000000;

	if (n % 2 == 0)
	{
		bool ok = 1;
		int n4 = 0, n7 = 0, flag = 0;
		for (int i = 1; i <= n; i++)
		if (flag)
		{
			if (n4 + 1 <= n / 2) res[i] = 4, n4++;
			else res[i] = 7, n7++;
		}
		else
		{
			if (st[i] < '4' && n4 + 1 <= n / 2) res[i] = 4, n4++, flag = 1;
			else if (st[i] == '4' && n4 + 1 <= n / 2 && a[i + 1] <= n / 2 - n7) res[i] = 4, n4++;
			else if (st[i] < '7' && n7 + 1 <= n / 2) res[i] = 7, n7++, flag = 1;
			else if (st[i] == '7' && n7 + 1 <= n / 2) res[i] = 7, n7++;
			else ok = 0;
		}
		if (ok)
		{
			for (int i = 1; i <= n; i++)
				printf("%d", res[i]);
			printf("\n");
			return 0;
		}
		n += 2;
	}else n++;
	for (int i = 1; i <= n / 2; i++)
		printf("4");
	for (int i = 1; i <= n / 2; i++)
		printf("7");
	return 0;
}
