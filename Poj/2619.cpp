#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;
#define abs(x) ((x) > 0 ? (x) : -(x))

int N, M;

void Calc()
{
	int alevel, blevel, aleft, bleft, aright, bright;
	alevel = 1; blevel = 1;
	for (int i = 1;; i += 2)
	{
		if (N - i <= 0)
		{
			aright = (i - N) / 2 + 1;
			aleft = (N + 1) / 2;
			break;
		}
		alevel++;
		N = N - i;
	}
	for (int i = 1;; i += 2)
	{
		if (M - i <= 0)
		{
			bright = (i - M) / 2 + 1;
			bleft = (M + 1) / 2;
			break;
		}
		blevel++;
		M = M - i;
	}
	int ans = abs(alevel - blevel) + abs(aleft - bleft) + abs(aright - bright);
	printf("%d\n", ans);
}

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &N, &M) != EOF)
	{
		Calc();
	}
	return 0;
}
