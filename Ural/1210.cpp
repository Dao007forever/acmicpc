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

const int INF = 1000000000;
int N, K;
int F[31][31];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < 31; i++)
	for (int j = 0; j < 31; j++)
		F[i][j] = INF;
	F[0][1] = 0;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &K);
		for (int j = 1; j <= K; j++)
		{
			int x, y;
			while (scanf("%d", &x) && x)
			{
				scanf("%d", &y);
				F[i][j] = min(F[i][j], F[i - 1][x] + y);
			}
		}
		char ch;
		if (i != N)
			scanf("\n%c", &ch);

	}
	int Min = INF;
	for (int i = 1; i < 31; i++)
		Min = min(Min, F[N][i]);
	printf("%d\n", Min);
	return 0;
}
