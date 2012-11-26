#include <cstdio>
#include <cstring>

int n, k;
char str[111111];

int main()
{
	freopen("in", "r", stdin);
	scanf("%d%d", &n, &k);
	scanf("%s", str + 1);
	int cnt = 0;
	for (int i = 1; i <= n && cnt < k; i++)
	{
		if (i % 2 == 0 && str[i] == '4' && str[i - 1] == '4' && str[i + 1] == '7')
		{
			if ((k - cnt) % 2 == 1) str[i] = '7';
			break;
		}
		if (str[i] == '4' && str[i + 1] == '7')
		{
			if (i % 2 == 1) str[i + 1] = '4';
			else str[i] = '7';
			cnt++;
		}
	}
	printf("%s\n", str + 1);
	return 0;
}
