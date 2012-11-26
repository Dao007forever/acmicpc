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

const int MAXN = 1000 + 10;
char st[MAXN], b[MAXN][MAXN];
char ch;
int n;
bool flag[MAXN];

bool cmp(int a, int b, char s1[], char s2[], int n)
{
	for (int i = 0; i < n; i++)
	{
		char c1 = s1[a + i];
		if (c1 >= 'A' && c1 <= 'Z') c1 = c1 - 'A' + 'a';
		char c2 = s2[b + i];
		if (c2 >= 'A' && c2 <= 'Z') c2 = c2 - 'A' + 'a';
		if (c1 != c2) return 0;
	}
	return 1;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%s", b[i]);
	scanf("%s\n", st);
	scanf("%c", &ch);

	for (int i = 0; st[i]; i++)
	{
		bool ok = 0;
		for (int k = 0; !ok && k < n; k++)
		{
			int len = strlen(b[k]);
			for (int j = 0; !ok && j <= i; j++)
			if (j + len - 1 >= i)
				ok |= cmp(j, 0, st, b[k], len);
		}
		flag[i] = ok;
	}

	if (ch >= 'a' && ch <= 'z') ch = ch - 'a' + 'A';

	for (int i = 0; st[i]; i++)
	{
		if (flag[i])
		{
			if (st[i] >= 'A' && st[i] <= 'Z')
			{
				if (st[i] == ch)
				{
					if (st[i] == 'A') st[i] = 'B';
					else st[i] = 'A';
				} else st[i] = ch;
			}
			else
			{
				if (st[i] == ch - 'A' + 'a')
				{
					if (st[i] == 'a') st[i] = 'b';
					else st[i] = 'a';
				}else st[i] = ch - 'A' + 'a';
			}
		}
	}
	printf("%s\n", st);
	return 0;
}
