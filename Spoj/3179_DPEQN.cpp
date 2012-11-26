#include <cstdio>
#include <cstring>

typedef long long LL;
LL a[111], ans[111], gcd[111], b, m;
int n;

LL Ex_Eulid(LL a, LL b, LL &x, LL &y)//x,y为方程方程为ax+by=gcd(a,b)的解,返回值为gcd(a,b)
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

void init()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", &a[i]);
	scanf("%lld%lld", &b, &m);
}

void solve()
{
	LL x = 0, y = 0;
	gcd[0] = m;
	for (int i = 1; i <= n; i++)
		gcd[i] = Ex_Eulid(gcd[i - 1], a[i], x, y);
	if (b % gcd[n] != 0)
	{
		puts("NO");
		return;
	}
	for (int i = n; i > 0; i--)
	{
		LL tmp = b;
		LL d = Ex_Eulid(a[i], gcd[i - 1], x, y);
		ans[i] = (x * (tmp / d) % m + m) % m;
//		if (ans[i] < 0) ans[i] += m;
		b = ((b - a[i] * ans[i]) % m + m) % m;
	}
	for (int i = 1; i <= n; i++)
	{
		if (i < n) printf("%lld ", ans[i]);
		else printf("%lld\n", ans[i]);
	}
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	for (scanf("%d", &Test); Test; Test--)
	{
		init();
		solve();
	}
	return 0;
}
