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

const int MAXN = 5000 + 10;
int N;
long long F[MAXN];
char st[MAXN];

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%s", st) != EOF)
	{
		memset(F, 0, sizeof(F));
		if (strcmp(st, "0") == 0) break;
		if (st[0] != '0') F[0] = 1;
		if (st[1] != '0') F[1] = F[0];
		char a[5] = {0};
		a[0] = st[0];
		a[1] = st[1];
		int num = atoi(a);
		if (num >= 1 && num <= 26) F[1]++;
		int len = strlen(st);
		for (int i = 2; i < len; i++)
		{
			if (st[i] != '0') F[i] = F[i - 1];
			a[0] = st[i - 1];
			a[1] = st[i];
			num = atoi(a);
			if (a[0] == '0') num = 0;
			if (num >= 1 && num <= 26) F[i] += F[i - 2];
		}
		printf("%I64d\n", F[len - 1]);
	}
	return 0;
}
