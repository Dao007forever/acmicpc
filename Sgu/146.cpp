#include <cstdio>
#include <iostream>
using namespace std;

int N;
long long L, T, V;

int main() {
	double l;
	scanf("%lf%d", &l, &N);
	L = (long long)(l * 10000 + 0.5);
	long long S = 0;
	for (int i = 0; i < N; i++) {
		cin >> T >> V;
		S = (S + V * T * 10000 % L) % L;

	}
	double ret = (double)min(S, L - S) / 10000.0;
	printf("%.4lf\n", ret);
	return 0;
	
}
