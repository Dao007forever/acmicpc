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

int a, b, mod;

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d%d", &a, &b, &mod);
	for (int i = 0; i <= a && i < mod; i++)
	{
		if ((mod - (long long)i * 1000000000 % mod) % mod > b)
		{
			printf("1 %.9d\n", i);
			return 0;
		}
	}
	printf("2\n");
	return 0;
}
