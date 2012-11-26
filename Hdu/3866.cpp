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
struct Person
{
	int id, m, c;
}P[MAXN];
int price, n;

bool cmp(Person a, Person b)
{
	if (a.m == b.m) return a.id < b.id;
	return a.m > b.m;
}

bool cmp1(Person a, Person b)
{
	return a.id < b.id;
}

int main()
{
	freopen("a", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		long long Sum = 0;
		scanf("%d%d", &price, &n);
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &P[i].m);
			P[i].id = i;
			Sum += (long long)P[i].m;
			P[i].c = 0;
		}

		if (Sum < price)
		{
			cout << "IMPOSSIBLE" << endl;
			continue;
		}

		sort(P, P + n, cmp);
		int cnt = n;
		while (price)
		{
			int ave = min(P[cnt - 1].m, price / cnt);
			if (ave)
			{
				price -= ave * cnt;
				for (int i = 0; i < cnt; i++)
				{
					P[i].m -= ave;
					P[i].c += ave;
				}
				while (P[cnt - 1].m == 0 && cnt > 0)
					cnt--;
			}
			else
			{
				for (int i = 0; i < price; i++)
				{
					P[i].m--;
					P[i].c++;
				}
				price = 0;
			}
		}
		sort(P, P + n, cmp1);
		for (int i = 0; i < n - 1; i++)
			printf("%d ", P[i].c);
		printf("%d", P[n - 1].c);
		cout << endl;
	}
	return 0;
}
