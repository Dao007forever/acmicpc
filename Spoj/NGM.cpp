#include <cstdio>

int main()
{
	int num;
	while (scanf("%d", &num) != EOF)
	{
		if (num == 0) 
		{
			printf("1\n");
			printf("0\n");
		}
		else
		{
			if (num % 10 == 0)
			{
				printf("2\n");
			}
			else
			{
				printf("1\n");
				printf("%d", num % 10);
			}
		}
	}
	return 0;
}
