#include <set>
#include <map>
#include <list>
#include <cmath>
#include <stack>
#include <queue>
#include <bitset>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000 + 10;
const int INF = 1000000000;
int N, M;
int old, now;
int F[2][MAXN];

void Init()
{
	F[1][0] = 0;
	for (int i = 1; i <= M; i++)
		F[1][i] = i;
}

void Solve()
{
	old, now = 1;
	for (int i = 2; i <= N; i++)
	{
		old = now;
		now = 1 - now;
		F[now][0] = 0;
		for (int j = 1; j <= M; j++)
		{
			F[now][j] = INF;
			for (int w = 1; w <= j; w++)
			{
				int temp = max(F[old][w - 1], F[now][j - w]) + 1;
				if (temp < F[now][j])
					F[now][j] = temp;
			}
		}
	}
}

int main()
{
	freopen("a.txt", "r", stdin);
	while (scanf("%d%d", &N, &M) != EOF)
	{
		if (N == 0 && M == 0) break;
		int temp = floor((log(M + 0.0) / log(2.0)) + 1.0);
		if (N >= temp) printf("%d\n", temp);
		else
		{
			Init();
			Solve();
			printf("%d\n", F[now][M]);
		}
	}
	return 0;
}
