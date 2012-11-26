#include <cstdio>
#include <iostream>
using namespace std;

long long ret1, ret2;
bool flag;
void calc(int a, int b, int c)
{
	if (flag) return;
	if (a == 1 && b == 1 && c == 1) 
	{
		flag = true;
		return;
	}
	ret2++;

	int Max = a;
	Max = b > Max ? b : Max;
	Max = c > Max ? c : Max;

	if (Max == a)
	{
		if (a & 1)
		{
			calc(a / 2 + 1, b, c);
		}
		else 
		{
			calc(a / 2, b, c);
		}
	}

	if (Max == b)
	{
		if (b & 1)
		{
			calc(a, b / 2 + 1, c);
		}
		else 
		{
			calc(a, b / 2, c);
		}
	}

	if (Max == c)
	{
		if (c & 1)
		{
			calc(a, b, c / 2 + 1);
		}
		else
		{
			calc(a, b, c / 2);
		}
	}
}

int main()
{
	freopen("in", "r", stdin);
	int Test, cas = 1, n, m, k;
	scanf("%d", &Test);
	while (Test--)
	{
		printf("Case #%d: ", cas++);
		scanf("%d%d%d", &n, &m, &k);
		flag = false;
		ret1 = (long long)n * m * k - 1LL;
		ret2 = 0;
		calc(n, m, k);
		cout << ret1 << " " << ret2 << endl;
	}
	return 0;
}
