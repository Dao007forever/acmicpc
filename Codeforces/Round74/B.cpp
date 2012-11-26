#include <cstdio>
#include <cstring>

const int MAXN = 100 + 10;
int n, m;
char a[MAXN][MAXN], temp[MAXN][MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", a[i]);
		strcpy(temp[i], a[i]);
	}

	for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++)
	{
		for (int k = 0; k < n; k++)
		if (k != i)
		{
			if (a[k][j] == a[i][j])
			{
				temp[i][j] = ' ';
				temp[k][j] = ' ';
			}
		}

		for (int k = 0; k < m; k++)
		if (k != j)
		{
			if (a[i][j] == a[i][k])
			{
				temp[i][j] = ' ';
				temp[i][k] = ' ';
			}
		}
	}

	char res[MAXN * MAXN];
	int t = 0;
	for (int i = 0; i < n; i++)
	for (int j = 0; j < m; j++)
	if (temp[i][j] != ' ')
	{
		res[t++] = temp[i][j];
	}
	printf("%s", res);
	return 0;
}
