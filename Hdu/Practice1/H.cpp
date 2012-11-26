#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 10000 + 10;
const int P = 9997;
int F[MAXN];
int main()
{
	F[1] = 2; F[2] = 4; F[3] = 7; F[4] = 12;
	for (int i = 5; i < 10001; i++)
		F[i] = (F[i - 1] + F[i - 2] + F[i - 4]) % P;
	int N;
	while (scanf("%d", &N) != EOF)
	{
		if (N == -1) break;
		cout << F[N] << endl;
	}
	return 0;
}
