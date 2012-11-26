#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

char Mas[3][10] = {"lios", "etr", "initis"};
char Fem[3][10] = {"liala", "etra", "inites"};
int cntMas[3], cntFem[3];

bool check(char *s, char *a)
{
	int l = strlen(a), n = strlen(s);
	int i = l - 1, j = n - 1;
	while (i >= 0)
	{
		if (a[i] != s[j]) return false;
		i--;
		j--;
	}
	return true;
}

int main()
{
	freopen("in", "r", stdin);
	char str[111111];
	int n = 0;
	bool flag = true;
	while (scanf("%s", str) != EOF)
	{
		n++;
		int len = strlen(str);
		bool ok = false;
		for (int k = 0; k < 3; k++)
		{
			if (check(str, Mas[k]))
			{
				cntMas[k]++;
				for (int i = k + 1; i < 3; i++)
					if (cntMas[i] != 0) flag = false;
				ok = true;
			}
			if (check(str, Fem[k]))
			{
				cntFem[k]++;
				for (int i = k + 1; i < 3; i++)
					if (cntFem[i] > 0) flag = false;
				ok = true;
			}
		}
		if (!ok) flag = false;
	}
	if (n == 1)
	{
        for (int i = 0; i < 3; i++)
        {
            if (cntMas[i] != 0 || cntFem[i] != 0) 
            {
                flag = true;
                break;
            }
        }
		if (flag) puts("YES");
		else puts("NO");
	}
	else
	{
		int cnt1 = 0, cnt2 = 0;
		for (int i = 0; i < 3; i++)
			cnt1 += cntMas[i], cnt2 += cntFem[i];
		if (cnt1 != 0 && cnt2 != 0) flag = false;
		if (cnt1 != 0 && cntMas[1] == 0 || cntMas[1] > 1) flag = false;
		if (cnt2 != 0 && cntFem[1] == 0 || cntFem[1] > 1) flag = false;
		if (flag) puts("YES");
		else puts("NO");
	}
	return 0;
}
