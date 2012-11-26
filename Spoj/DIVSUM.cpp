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

const int MAXN =500000;
int F[MAXN + 10];

int main()
{
	freopen("a", "r", stdin);
	memset(F, 0, sizeof(F));
	for (int i = 1; i <= MAXN; i++)
	{
		for (int j = 2; i * j <= MAXN; j++)
		{
			F[i * j] += i;
		}
	}
	int T;
	scanf("%d", &T);
	while (T--)
	{
		int N;
		scanf("%d", &N);
		printf("%d\n", F[N]);
	}
	return 0;
}
