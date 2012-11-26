#include <cstdio>
#include <cstring>

char s[1000000];

int main()
{
	freopen("a", "r", stdin);
	scanf("%s", s);
	int len = strlen(s), n = 0;
	for (int i = 0; i < len; i++)
	{
		if (n && s[i] == s[n - 1])
		{
			n--;
		}
		else
		{
			s[n++] = s[i];
		}
	}
	s[n]= 0;
	puts(s);
	return 0;
}
