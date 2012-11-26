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

#define REP(i, n) for(i = 0; i < (n); ++i)
#define FOR(i, l, h) for(i = (l); i <= (h); ++i)
#define FORD(i, h, l) for(i = (h); i >= (l); --i)

const int MAXK = 205;
int N;
int A[MAXK], D[MAXK];
bool B[MAXK], C[MAXK];
bool Map[MAXK][MAXK];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	int i, j, k, K;
	memset(Map, 1, sizeof(Map));
	FOR(i, 1, N * (N - 1) / 2)
	{
		scanf("%d", &K);
		memset(B, 0, sizeof(B));
		FOR(j, 1, K)
		{
			scanf("%d", A + j);
			B[A[j]] = 1;
			C[A[j]] = 1;
		}
		if (N == 2)
		{
			printf("1 %d\n", A[K]);
			printf("%d ", K - 1);
			for (int j = 1; j < K; j++)
				printf("%d%c", A[j], (j == N - 1) ? '\n' : ' ');
			return 0;
		}
		FOR(j, 1, K)
		{
			FOR(k, 1, MAXK - 1)
			if (!B[k])
			{
				Map[A[j]][k] = Map[k][A[j]] = 0;
			}
		}
	}
	FOR(i, 1, MAXK - 1)
	if (C[i])
	{
		bool Need = 1;
		FOR(j, 1, i - 1)
		{
			if (C[j] && Map[i][j])
				Need = 0;
		}
		if (Need)			
		{
			int T = 0;
			FOR(j, i, MAXK - 1)
			{
				if (C[j] && Map[i][j])
					D[++T] = j;
			}
			printf("%d ", T);
			FOR(j, 1, T)
			{
				printf("%d%c", D[j], (j == T) ? '\n' : ' ');
			}
		}
	}
	return 0;
}
