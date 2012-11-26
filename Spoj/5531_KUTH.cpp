#include <cstdio>

int n, m;

int gcd(int a, int b)
{
	return !b ? a : gcd(b, a % b);
}

int read()
{
	int res = 0, flag = 0;
	for (;;)
	{
		char ch = getchar();
		if (ch >= '0' && ch <= '9') res = res * 10 + ch - '0', flag = 1;
		else if (flag) return res;
	}
}

int main()
{
	freopen("in", "r", stdin);

	n = read(); m = read();
	int g = 360000000;
	for (int i = 0; i < n; i++)
		g = gcd(g, read() * 1000000 + read());
	for (int i = 0; i < m; i++)
		printf("%s\n", !((read() * 1000000 + read()) % g) ? "YES" : "NO");
	return 0;
}
