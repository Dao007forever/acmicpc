#include <cstdio>
#include <cstring>

char s[111];

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%s", s);
	int n = strlen(s);
	int i = 0, cnt = 1;
	char now = s[0];
	int ret = 1;
	for (i = 1; i < n; i++) {
		while (s[i] == now && cnt < 5) {
			i++;
			cnt++;
		}
		if (i >= n) break;
		cnt = 1;
		now = s[i];
		ret++;
	}
	printf("%d\n", ret);
}
