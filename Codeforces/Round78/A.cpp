#include <cstdio>
#include <cstring>

char x[1005];
void output(int n, int k)
{
	int len = k;
	int res[1005] = {0};
	for (int i = 0; i < k; i++)
		res[i + 1] = x[i] - '0';
	res[k] += n;
	while (res[k] >= 10 && k > 0)
	{
		res[k] -= 10;
		res[k - 1]++;
		k--;
	}
	if (res[0] == 0)
	{
		for (int i = 1; i <= len; i++)
			printf("%d", res[i]);
	}
	else
	{
		for (int i = 0; i <= len; i++)
			printf("%d", res[i]);
	}
}
int main()
{
	freopen("a", "r", stdin);
	scanf("%s", x);
	int k;
	for (int i = 0; i < strlen(x); i++)
		if (x[i] == '.')
		{
			k = i;
			break;
		}
	if (x[k - 1] == '9') printf("GOTO Vasilisa.\n");
	else
	{
		if (x[k + 1] >= '5')
			output(1, k);
		else
		{
			for (int i = 0; i < k; i++)
				printf("%c", x[i]);
		}
	}
	return 0;
}
