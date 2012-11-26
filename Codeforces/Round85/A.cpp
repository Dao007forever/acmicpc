#include <cstdio>
#include <cstring>

char a[111], b[111];

int main()
{
	freopen("a", "r", stdin);
	scanf("%s", a);
	scanf("%s", b);
	for (int i = 0; i < strlen(a); i++)
	if ('A' <= a[i] && a[i] <= 'Z')
		a[i] = 'a' + a[i] - 'A';
	for (int i = 0; i < strlen(b); i++)
	if ('A' <= b[i] && b[i] <= 'Z')
		b[i] = 'a' + b[i] - 'A';
	if (strcmp(a, b) < 0) printf("-1\n");
	else if (strcmp(a, b) == 0) printf("0\n");
	else printf("1\n");
	return 0;
}
