#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 10000 + 10;
int N;
int a[MAXN];

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) && N != -1)
	{
		long long Sum = 0;
		for (int i = 0; i < N; i++)
		{
			scanf("%d", a + i);
			Sum += a[i];
		}
		if (Sum % N != 0)
		{
			cout << -1 << endl;
		}
		else
		{
			long long ave = Sum / N, res = 0;
			for (int i = 0; i < N; i++)
			if (a[i] < ave)
			{
				res += ave - a[i];
			}
			cout << res << endl;
		}
	}
	return 0;
}
