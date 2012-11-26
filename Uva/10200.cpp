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

int a, b;
int sum[11111];

bool check(int x)
{
	if (x == 0 || x == 1) return false;
	if (x == 2) return true;
	if (x % 2  == 0) return false;
	for (int i = 3; i <= sqrt(x); i+=2)
	if (x % i == 0) return false;
	return true;
}

void prepare()
{
	for (int i = 0; i <= 10000; i++)
	{
		if (check(i * i + i + 41)) sum[i] = sum[i - 1] + 1;
		else sum[i] = sum[i - 1];
	}
}

int main()
{
	freopen("a", "r", stdin);
	prepare();
	while (scanf("%d%d", &a, &b) != EOF)
	{
		double ans = (double)(sum[b] - sum[a - 1]) * 100 / (b - a + 1) + 1e-5;
		printf("%.2lf\n", ans);
	}
	return 0;
}
