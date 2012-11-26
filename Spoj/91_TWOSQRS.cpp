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

long long n;
long long sqr[1111111];

int main()
{
	freopen("a", "r", stdin);
	int p = 0;
	for (int i = 0; i <= 1000000; i++)
		sqr[p++] = (long long)i * i;
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		cin >> n;
		int i = 0, f = 0, j = lower_bound(sqr, sqr + p, n) - sqr;
		while (!f && i <= j)
		{
			if (sqr[i] + sqr[j] >= n)
			{
				if (sqr[i] + sqr[j] == n) f = 1;
				j--;
			}
			else i++;
		}
		if (f) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
