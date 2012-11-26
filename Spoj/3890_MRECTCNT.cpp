#include <cstdio>
#include <iostream>
using namespace std;

int Euler(int n) {
	if (n == 2) return 2;
	int ret = 1;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			n /= i;
			ret *= (i - 1);
			while (n % i == 0)
				n /= i, ret *= i;
		}
	}
	if (n > 1) ret *= n - 1;
	return ret;
}

int main()
{
	int n;
	scanf("%d", &n);
	long long ret = 0;
	for (int i = 1; i * i <= n; i++)
		if (n % i == 0) {
			ret += (long long)Euler(i + 1);
			if (i * i != n)
				ret += (long long)Euler(n / i + 1);
		}
	cout << ret / 2 << endl;
}
