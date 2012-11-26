#include <cstdio>
#include <cstring>

char s1[111], s2[111], s3[111];
int num[33];

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%s", s1);
	int n = strlen(s1);
	for (int i = 0; i < n; i++)
		num[s1[i] - 'A']++;
	scanf("%s", s2);
	n = strlen(s2);
	for (int i = 0; i < n; i++)
		num[s2[i] - 'A']++;
	scanf("%s", s3);
	n = strlen(s3);
	for (int i = 0; i < n; i++)
		num[s3[i] - 'A']--;
	bool flag = true;
	for (int i = 0; i < 26; i++)
		if (num[i] != 0) {
			flag = false;
			break;
		}
	if (flag) puts("YES");
	else puts("NO");
	return 0;
}
