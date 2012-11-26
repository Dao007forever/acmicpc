#include <cstdio>

int n;
int a[111];

void swap(int &a, int &b) {
	int t = a;
	a = b;
	b = t;
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	int min = 10000, max = 0;
	int k1, k2;
	int ret = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		if (a[i] <= min) {
			min = a[i];
			k2 = i;
		}
	}
	ret += n - 1 - k2;
	for (int i = k2; i < n - 1; i++)
		swap(a[i], a[i + 1]);
	for (int i = 0; i < n; i++) {
		if (a[i] > max) {
			max = a[i];
			k1 = i;
		}
	}
	ret += k1;
	printf("%d\n", ret);
	return 0;
}
