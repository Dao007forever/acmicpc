#include <cstdio>
#include <iostream>
using namespace std;

const int MAXN = 100 + 10;
int N;
long long f[MAXN], a[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		cin >> a[i];
	}
	f[1] = (long long)a[1];
	for (int i = 2; i <= N; i++)
	{
		f[i] += f[i - 1] + (long long)(a[i] - 1) * i;
		f[i]++;
	}
	cout << f[N] << endl;
	return 0;
}
