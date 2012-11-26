#include <cstdio>
#include <iostream>
using namespace std;

typedef long long LL;

LL N;

int main()
{
	cin >> N;
	LL Max = -1, Min = 1LL << 45;
	for (int i = 1; i * i <= N; i++) {
		if (N % i == 0) {
			int m = N / i;
			for (int j = 1; j * j <= m; j++) {
				if (m % j == 0) {
					int k = m / j;
					LL ret = (LL)(i + 1)*(j + 2)*(k + 2) - N;
					Min = min(Min, ret);
					Max = max(Max, ret);
				}
			}

			int t = i;
			i = N / i;
			m = N / i;
			for (int j = 1; j * j <= m; j++) {
				if (m % j == 0) {
					int k = m / j;
					LL ret = (LL)(i + 1)*(j + 2)*(k + 2) - N;
					Min = min(Min, ret);
					Max = max(Max, ret);
				}
			}
			i = t;
		}
	}
	cout << Min << " " << Max << endl;
	return 0;
}
