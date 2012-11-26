#include <cstdio>

int main() {
	int k;
	scanf("%d", &k);
	if (k == 1) {
		printf("8\n");
		return 0;
	}
	int cnt = 1;
	if ((k - 1) % 3 == 0) {
		cnt += 2;
		if ((k - 1) % 6 == 0) {
			cnt++;
		}
	}
	printf("%d\n", cnt);
	return 0;
}
