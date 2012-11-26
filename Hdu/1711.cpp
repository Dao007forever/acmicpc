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

const int MAXN = 1000000 + 10;
const int MAXM = 10000 + 10;
int T, N, M;
int A[MAXN], B[MAXM], next[MAXN];

void Get_next()
{
	next[1] = 0;
	for (int i = 2, j = 0; i <= M; i++)
	{
		while (j > 0 && B[j + 1] != B[i])
			j = next[j];
		if (B[j + 1] == B[i]) j++;
		next[i] = j;
	}
}

int KMP()
{
	Get_next();
	for (int i = 1, j = 0; i <= N; i++)
	{
		while (j > 0 && B[j + 1] != A[i])
			j = next[j];
		if (B[j + 1] == A[i]) j++;
		if (j == M)
		{
			return i - M + 1;
			j = next[j];
		}
	}
	return -1;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++)
			scanf("%d", &A[i]);
		for (int i = 1; i <= M; i++)
			scanf("%d", &B[i]);

		printf("%d\n", KMP());
	}
	return 0;
}
