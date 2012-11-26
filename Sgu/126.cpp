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

const int INF = 2147483647;
int A, B;
int F[50];

int gcd(int a, int b)
{
	return (b == 0 ? a : gcd(b, a % b));
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &A, &B);
	int G = gcd(A, B);
	int temp = (A + B) / G;
	int tot = 0;
	F[0] = 1;
	for (int i = 1; F[i - 1] <= INF / 2; i++)
	{
		F[i] = F[i - 1] * 2;
		tot++;
	}
	bool ok = false;
	int i = 0;
	for (i = 0; i <= tot; i++)
	if (temp == F[i])
	{
		ok = true;
		break;
	}
	if (A == 0 || B == 0)
	{
		printf("0\n");
	}
	else if (!ok)
	{
		printf("-1\n");
	}
	else
	{
		printf("%d\n", i);
	}
	return 0;
}
