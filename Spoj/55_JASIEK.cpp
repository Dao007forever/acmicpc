#include <cstdio>

int main()
{
	freopen("a", "r", stdin);
	int ans, x, y;
	char ch;
	for (int t = 10; t > 0; t--)
	{
		ans = 2;
		x = 0;
		y = 0;
		do scanf("%c", &ch);
		while (ch <= ' ');
		while (ch != 'K')
		{
			ans++;
			switch (ch)
			{
				case 'E':
					ans -= y;
					x++;
					break;
				case 'W':
					ans += y;
					x--;
					break;
				case 'N':
					ans += x;
					y++;
					break;
				case 'S':
					ans -= x;
					y--;
					break;
			};
			do scanf("%c", &ch);
			while (ch <= ' ');
		}
		ans /= 2;
		printf("%d\n", ans);
	}
	return 0;
}
