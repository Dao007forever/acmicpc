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

const int MAXN = 200000 + 10;
int N, K;
int w[MAXN], ma[MAXN][32];

void RMQinit()
{
	int j , m;
	for (int i = 1 ; i <= N ; i++)
	{
		ma[i][0] = w[i];
	}
	m = floor(log((double)N) / log(2.0));
	for (int i = 1 ; i <= m ; i++)
	{
		for (int j = N ; j >= 1 ; j--)
		{
			ma[j][i] = ma[j][i - 1];
			if (j + (1 << (i - 1)) <= N)
				ma[j][i] = max(ma[j][i] , ma[j + (1 << (i - 1))][i - 1]);
		}
	}
}

int RMQmax(int l , int r)
{
	int k = floor(log((double)(r - l + 1)) / log(2.0));
	return max(ma[l][k] , ma[r - (1 << k) + 1][k]);
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &N, &K) != EOF)
	{
		if (N == -1 && K == -1) break;
		int Sum = 0;
		for (int i = 1; i <= N; i++)
		{
			scanf("%d", &w[i]);
			Sum += w[i];
		}
		RMQinit();
		if (Sum < K) printf("-1\n");
		else
		{
			int Left = 1, Right = N;
			int res;
			while (Left <= Right)
			{
				int Mid = (Left + Right) / 2;
				int maxsum = 0, count = 0;
				for (int i = 1; i + Mid <= N + 1; i += Mid)
				{
					maxsum += RMQmax(i, i + Mid - 1);
					count++;
					if (maxsum > K) break;
				}
				if (maxsum <= K)
					Right = Mid - 1;
				else
				{
					Left = Mid + 1;
					res = count;
				}
			}
			printf("%d\n", res);
		}
	}
	return 0;
}
