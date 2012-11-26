#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAX(a, b) (a > b ? a : b)

map<int, long long> h;

long long f(int n)
{
	if (n == 0) return 0;

	long long r = h[n];

	if (r == 0)
	{
		r = MAX(n, f(n / 2) + f(n / 3) + f(n / 4));
		h[n] = r;
	}
	return r;
}

int main()
{
	int n;
	while (scanf("%d", &n) != EOF)
	{
		cout << f(n) << endl;
	}
	return 0;
}
