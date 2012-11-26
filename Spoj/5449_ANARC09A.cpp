#include <cstdio>
#include <cstring>

const int maxn = 2005;
char str[maxn];

int main() {
	freopen("in.txt", "r", stdin);
	int test = 0;
	while (scanf("%s", str) && *str != '-') {
		int ret = 0, cnt = 0;
		for (int i = 0; str[i] == '{' || str[i] == '}'; i++)
			if (str[i] == '{') cnt++;
			else if (cnt) cnt--;
			else {
				ret++;
				cnt++;
			}
		printf("%d. %d\n", ++test, ret + cnt / 2);
	}
	return 0;
}
