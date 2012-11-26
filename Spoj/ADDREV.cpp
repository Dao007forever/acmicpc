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

int N;

int Rev(int x)
{
	char s[20] = {0};
	int tot = 0;
	while (x)
	{
		s[tot++] = '0' + x % 10;
		x /= 10;
	}
	int num = atoi(s);
	return num;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		int d1 = Rev(a), d2 = Rev(b);
		int d3 = d1 + d2;
		int res = Rev(d3);
		printf("%d\n", res);
	}
	return 0;
}
