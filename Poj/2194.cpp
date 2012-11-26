#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

int N;
double y, x[10];

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) && N)
	{
		for (int i = 0; i < N; i++)
			cin >> x[i];
		sort(x, x + N);

		y = 1.0;
		for (int i = 0; i < N - 1; i++)
		{
			y += sqrt(4 - (x[i + 1] - x[i]) * (x[i + 1] - x[i]) / 4);
		}
		printf("%.4lf %.4lf\n", (x[0] + x[N - 1]) / 2, y);
	}
	return 0;
}
