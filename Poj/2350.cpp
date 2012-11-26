#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 1000 + 10;
int N;
int a[MAXN];

int main()
{
	freopen("a", "r", stdin);
	int T;
	cin >> T;
	while (T--)
	{
		cin >> N;
		int sum = 0;
		for (int i = 1; i <= N; i++)
		{
			cin >> a[i];
			sum += a[i];
		}
		double ave = (double)sum / N;
		int tot = 0;
		for (int i = 1; i <= N; i++)
		if (a[i] * 1.0 > ave)
		{
			tot++;
		}
		double res = (double)tot * 100.0 / N;
		printf("%.3lf%%\n", res);
	}
	return 0;
}
