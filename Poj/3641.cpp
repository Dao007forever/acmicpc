#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

int a, p;

int quickpow(int m, int n, int k)
{
	long long b = 1;
	while (n > 0)
	{
		if (n & 1) b = (long long)b * m % k;
		n = n >> 1;
		m = (long long)m * m % k;
	}
	return (int)b;
}

bool prime(int x)
{
	if (x == 2) return true;
	if (x % 2 == 0) return false;
	for (int i = 3; i <= sqrt((double)x); i += 2)
		if (x % i == 0) return false;
	return true;
}

int main()
{
	freopen("a", "r", stdin);
	while (cin >> p >> a)
	{
		if (a == 0 && p == 0) break;
		if (quickpow(a, p, p) == a && !prime(p)) cout << "yes" << endl;
		else cout << "no" << endl;
	}
	return 0;
}
