#include <cstdio>
#include <iostream>
using namespace std;

int T;
int N, K;
long long res;

void Calc()
{
	int i = N - K;
	long long j;
	if (N == K || K == 0)
	{
		res = 1;
	}
	else if (K == 1)
	{
		res = N;
	}
	else if (i > K)
	{
		j = 1;
		res = 1;
		while (j <= K)
		{
			if (N % j == 0)
				res = res * ((long long)N / j);
			else if (res % j == 0)
				res = (long long)N * (res / j);
			else res = (N * res) / j;
			j++;
			N--;
		}
	}
	else if (i <= K)
	{
		j = 1;
		res = 1;
		while (j <= i)
		{
			if (N % j == 0)
				res = res * ((long long)N / j);
			else if (res % j == 0)
				res = (long long)N * (res / j);
			else res = (N * res) / j;
			j++;
			N--;

		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	cin >> T;
	while (T--)
	{
		cin >> N >> K;
		N--; K--;
		Calc();
		cout << res << endl;
	}
}
