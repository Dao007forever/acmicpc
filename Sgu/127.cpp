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

const int MAXN = 8000 + 10;
int K, N;
int F[15];

int main()
{
	freopen("a", "r", stdin);
	memset(F, 0, sizeof(F));
	scanf("%d", &K);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		int num;
		scanf("%d", &num);
		F[num / 1000]++;
	}
	int res = 0;
	for (int i = 1; i <= 9; i++)
	{
		if (F[i] % K == 0) res += F[i] / K;
		else res += F[i] / K + 1;
	}
	printf("%d\n", res + 2);
	return 0;
}
