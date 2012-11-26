#include <cstdio>

char s[1024] = "ROYGBIV";

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 7; i < n; i++)
		s[i] = s[(i - 7) % 4 + 3];
	puts(s);
	return 0;
}
