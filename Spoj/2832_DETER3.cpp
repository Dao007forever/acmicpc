#include <cstdio>
#include <iostream>
using namespace std;

int N;
long long P, matrix[222][222], ans;

void swap(long long &a, long long &b)
{
	long long tmp = a; a = b; b = tmp;
}

void init()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			scanf("%lld", &matrix[i][j]);
			matrix[i][j] %= P;
			if (matrix[i][j] < 0) matrix[i][j] += P;
		}
}

long long solve()
{
	ans = 1;
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		if (matrix[j][i])
		{
			for (int k = 0; k < N; k++)
				swap(matrix[i][k], matrix[j][k]);
			ans = -ans;
			break;
		}

		for (int j = i + 1; j < N; j++)
		{
			while (matrix[j][i])
			{
				long long t = matrix[i][i] / matrix[j][i];
				for (int k = i; k < N; k++)
				{
					matrix[i][k] -= matrix[j][k] * t;
					matrix[i][k] %= P;
					swap(matrix[i][k], matrix[j][k]);
				}
				ans = -ans;
			}
		}
		ans *= matrix[i][i];
		ans %= P;
		if (!ans) return 0;
	}
	if (ans < 0) ans += P;
	return ans;
}

int main()
{
	freopen("in", "r", stdin);
	while (scanf("%d%lld", &N, &P) != EOF)
	{
		init();
		cout << solve() << endl;
	}
}
