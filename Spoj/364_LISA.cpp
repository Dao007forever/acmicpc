#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100 + 10;
char oper[MAXN];
unsigned long long Num[MAXN], Max[MAXN][MAXN], Min[MAXN][MAXN];

int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		int n = 0, i;
		char ch = '+';
		for (i = 0; ch == '+' || ch == '*'; i++)
		{
			cin >> Num[i];
			cin.get(ch);
			if (ch == '+' || ch == '*')
				oper[i] = ch;
		}
		n = i;
		memset(Min, 255, sizeof(Min));
		memset(Max, 0, sizeof(Max));

		for (int len = 0; len < n; len++)
			for (int i = 0; i + len < n; i++)
			{
				int j = i + len;
				if (i == j)
				{
					Max[i][j] = Min[i][j] = Num[i];
				}
				else
				{
					for (int k = i; k < j; k++)
					{
						int tmp;
						if (oper[k] == '+')
							tmp = Max[i][k] + Max[k + 1][j];
						else tmp = Max[i][k] * Max[k + 1][j];
						if (tmp > Max[i][j]) Max[i][j] = tmp;
						
						if (oper[k] == '+')
							tmp = Min[i][k] + Min[k + 1][j];
						else tmp = Min[i][k] * Min[k + 1][j];
						if (tmp < Min[i][j]) Min[i][j] = tmp;
					}
				}
			}
		cout << Max[0][n - 1] << " " << Min[0][n - 1] << endl;
	}
	return 0;
}
