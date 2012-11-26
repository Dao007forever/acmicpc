#include <cstdio>
#include <cstring>

const int MAXN = 30000 + 10;
int N;

int main()
{
	freopen("a", "r", stdin);
	scanf("%d\n", &N);
	int ans = 0, sum = 0;
	for (int i = 0; i < N;)
	{
		char ch;
		scanf("%c", &ch);
		if (ch == '>') sum++, i++;
		else if (ch == '<') ans += sum, i++;
	}
	printf("%d\n", ans);
	return 0;
}
