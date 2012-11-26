#include <cstring>
#include <cstdio>
using namespace std;

int F[5];

int main()
{
	freopen("a", "r", stdin);
	memset(F, 0, sizeof(F));
	char st[200];
	for (int i = 0; i < 3; i++)
	{
		gets(st);
		int len = strlen(st);
		for (int j = 0; j < len; j++)
		{
			if (st[j] == 'a' || st[j] == 'e' || st[j] == 'i' || st[j] == 'o' || st[j] == 'u')
				F[i]++;
		}
	}
	if (F[0] == 5 && F[1] == 7 && F[2] == 5) puts("YES");
	else puts("NO");
	return 0;
}
