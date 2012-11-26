#include <cstdio>
#include <cmath>

const int maxn = 2800000 + 10;
double fac[maxn], val[maxn];
int ret[1000001];

int main() {
	freopen("in.txt", "r", stdin);
	for (int i = 1; i <= 2800000; i++) {
		val[i] = log(i);
		fac[i] = fac[i - 1] + val[i];
	}

	ret[0] = 1;
	for (int i = 1; i <= 1000000; i++) {
		ret[i] = ret[i - 1];
		for (; fac[ret[i]] <= val[i] * ret[i]; ret[i]++);
	}

	int Test;
	scanf("%d", &Test);
	while (Test--) {
		int a;
		scanf("%d", &a);
		printf("%d\n", ret[a]);
	}
	return 0;
}
