#include <cstdio>
#include <algorithm>
using namespace std;

int k;
int a[15];

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &k);
	int s = 0;
	for (int i = 1; i <= 12; i++)
		scanf("%d", &a[i]), s += a[i];
	if (s < k) {
		printf("-1\n");
		return 0;
	}else {
		if (k == 0) {
			printf("0\n");
			return 0;
		}
		sort(a + 1, a + 12 + 1);
		int s = 0, ret = 0;
		for (int i = 12; i >= 1; i--) {
			s += a[i];
			ret++;
			if (s >= k) {
				break;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
