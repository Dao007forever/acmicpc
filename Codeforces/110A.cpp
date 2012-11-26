#include <cstdio>
#include <iostream>
using namespace std;

bool isLucky(long long n)
{
	int t = 0;
	while (n)
	{
		if (n % 10 == 4 || n % 10 == 7) t++;
		n /= 10;
	}
	if (t == 4 || t == 7) return true;
	return false;
}

int main()
{
	long long n;
	cin >> n;
	if (isLucky(n)) puts("YES");
	else puts("NO");
	return 0;
}
