#include <cstdio>
#include <iostream>
using namespace std;

const int P = 987654321;
int main()
{
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		if (n == -1 && m == -1) break;
		long long ans = 1;
		if (n < m)
		{
			for (int i = 1; i <= n; i++)
				ans = (long long)(ans * m) % P;
			cout << ans << endl;
		}
		else
		{
			if (m == 1) 
			{
				ans = 1;
			}
			else 
			{
				if (m == 2)
				{
					for (int i = 1; i <= n; i++)
						ans = (long long)(ans * m) % P;
				}
				else
				{
					for (int i = 1; i <= m; i++)
						ans = (long long)(ans * i) % P;
					ans += m;
					ans %= P;
				}
			}
			cout << ans << endl;
		}
	}
	return 0;
}
