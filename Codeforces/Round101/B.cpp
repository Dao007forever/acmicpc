#include <cstdio>

int a, x, y;

void no() {
	printf("-1\n");
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d%d%d", &a, &x, &y);
	if (y % a == 0) {
		no();
		return 0;
	}
	else {
		int l = y / a;
		if (l == 0) {
			if (2 * x == a || 2 * x > a || 2 * x == -a || 2 * x < -a) {
				no();
				return 0;
			}
			else {
				printf("1\n");
				return 0;
			}
		}
		else if (l % 2 == 1) {
			if (2 * x == a || 2 * x > a || 2 * x == -a || 2 * x < -a) {
				no();
				return 0;
			}
			else {
				int ret = (3 * l + 1) / 2;
				printf("%d\n", ret);
				return 0;
			}
		}
		else {	   
			if (x == a || x > a || x == -a || x < -a || x == 0) {
				no();
				return 0;
			}
			else if (x < 0) {
				l--;
				int ret = (3 * l + 1) / 2 + 1;
				printf("%d\n", ret);
				return 0;
			}
			else {
				l--;
				int ret = (3 * l + 1) / 2 + 2;
				printf("%d\n", ret);
				return 0;
			}
		}
	} 
}
