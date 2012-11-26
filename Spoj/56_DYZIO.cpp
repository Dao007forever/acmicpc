#include <cstdio>

const int MAXN = 20001;
int stack[MAXN];
int sp, best, bp, op, n;
char str[MAXN];

int main()
{
	freopen("56", "r", stdin);
	int t;
	for (int cas = 1; cas <= 10; cas++)
	{
		scanf("%d%s", &n, str);
		sp = 0;
		best = -1;
		bp = 0;
		op = 0;
		for (int i = 0; i < n; i++)
		{
			if (str[i] == '1')
			{
				op++;
				stack[sp++] = 2;
				if (sp > best)
				{
					best = sp;
					bp = op;
				}
			}
			else
			{
				while (sp > 0 && stack[sp - 1] == 1)
					sp--;
				if (sp > 0 && stack[sp - 1] == 2)
					stack[sp - 1]--;
			}
		}
		printf("%d\n", bp);
	}
	return 0;
}
