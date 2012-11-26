#include <cstdio>
#include <cstring>

int main() {
	char str[111];
	scanf("%s", str);
	int n = strlen(str);
	bool flag = false;
	for (int i = 0; i < n; i++) {
		if (str[i] == 'H' || str[i] == 'Q' || str[i] == '9')
			flag = true;
	}
	if (flag) puts("YES");
	else puts("NO");
	return 0;
}
