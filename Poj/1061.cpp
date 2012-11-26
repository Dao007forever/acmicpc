#include <cstdio>
#include <iostream>
using namespace std;

typedef long long LL;

LL Ex_Eulid(LL a, LL b, LL &x, LL &y)
{
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	LL r = Ex_Eulid(b, a % b, x, y);
	LL tmp = x;
	x = y;
	y = tmp - (a / b) * y;
	return r;
}


int main()
{
	freopen("a", "r", stdin);
	LL a, b, m, n, l, x, y, d, t, p;
	while (scanf("%lld%lld%lld%lld%lld", &a, &b, &m, &n, &l) != EOF)
	{
		if (a != b && m == n)
		{
			puts("Impossible\n");
			continue;
		}
		t = m - n;
		p = b - a;
		if (t < 0)
		{
			t = -t;
			p = -p;
		}
		d = Ex_Eulid(t, l, x, y);
		if (p % d != 0)
		{
			printf("Impossible\n");
			continue;
		}
		x = x * p / d;
		l = l / d;
		x = (x % l + l) % l;
		cout << x << endl;
	}
	return 0;
}
