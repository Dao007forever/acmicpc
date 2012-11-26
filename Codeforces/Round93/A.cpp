#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

long long t1, t2, x1, x2, t0;

int main()
{
	freopen("in", "r", stdin);
	cin >> t1 >> t2 >> x1 >> x2 >> t0;
	if (t1 == t2)
	{
		cout << x1 << " " << x2 << endl;
		return 0;
	}
	if (t0 == t1)
	{
		cout << x1 << " 0" << endl;
		return 0;
	}
	if (t0 == t2)
	{
		cout << "0 " << x2 << endl;
		return 0;
	}

	long long y1 = -1, y2 = -1, mn = -1, md = -1;
	for (long long i = 0, j; i <= x1; i++)
	{
		if (i == 0) j = x2;
		else j = (t0 * i - t1 * i + t2 - t0 - 1) / (t2 - t0);
		if (j > x2) continue;

		long long n = t1 * i + t2 * j, d = i + j;
		if (n < t0 * d) continue;
		if (mn == -1 || n * md < mn * d || (n * md == mn * d && (i + j > y1 + y2)))
		{
			mn = n;
			md = d;
			y1 = i;
			y2 = j;
		}
	}
	cout << y1 << " " << y2 << endl;
	return 0;
}
