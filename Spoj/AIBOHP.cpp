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

const int MAXN = 6100 + 10;
char str[MAXN];
int F[2][MAXN];

int main()
{
	freopen("a", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%s", str);
		memset(F, 0, sizeof(F));
		int N = strlen(str);
		int k = 0;
		for (int i = N - 2; i >= 0; i--)
		{
			for (int j = i; j < N; j++)
			{
				if (str[i] == str[j])
					F[k][j] = F[1 - k][j - 1];
				else F[k][j] = min(F[1 - k][j], F[k][j - 1]) + 1;
			}
			for (int j = 0; j < N; j++)
				F[1 - k][j] = 0;
			k = 1 - k;
		}
		printf("%d\n", F[1 - k][N - 1]);
	}
	return 0;
}
