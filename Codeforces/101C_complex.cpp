#include <cstdio>
#include <iostream>
#include <complex>
using namespace std;

int main()
{
	freopen("a", "r", stdin);
	long long xa, ya, xb, yb, xc, yc;
	cin >> xa >> ya >> xb >> yb >> xc >> yc;
	complex<long long> a(xa, ya), b(xb, yb), c(xc, yc);

	complex<long long> e(1, 0), i(0, 1);
	for (long long t = 0; t < 4; t++, e *= i)
	{
		complex<long long> n = b - e * a;
		if (norm(c) == 0)
		{
			if (norm(n) == 0)
			{
				cout << "YES" << endl;
				return 0;
			}
		}
		else
		{
			complex<long long> d = n / c;
			if (c * d == n)
			{
				cout << "YES" << endl;
				return 0;
			}
		}
	}
	cout << "NO" << endl;
	return 0;
}
