#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

int calc(int x) {
	int ret = 0;
	for (int i = 1; i <= (int)sqrt(x); i++)
		if (x % i == 0) ret++;
	return ret;
}

int main() {
	int n;
	long long ret = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		ret += calc(i);
	}
	cout << ret << endl;
	return 0;
}
