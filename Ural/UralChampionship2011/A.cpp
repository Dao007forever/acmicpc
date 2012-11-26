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

const int MAXN = 100;
int N;
int res;
char Start[MAXN], End[MAXN];

void DFS(char *s, int step)
{
	if (strcmp(s, End) == 0)
	{
		if (step < res)
		{
			res = step;
			return;
		}
	}
	if (step > res) return;

	if (s[0] == '1')
	{
		s[0] = '0';
		DFS(s, step + 1);
		s[0] = '1';
	}

	if (s[0] == '0')
	{
		s[0] = '1';
		DFS(s, step + 1);
		s[0] = '0';
	}

	int len = strlen(s);
	int k;
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '1')
		{
			k = i;
			break;
		}
	}
	if (k < len - 1)
	{
		if (s[k + 1] == '1')
		{
			s[k + 1] = '0';
			DFS(s, step + 1);
			s[k + 1] = '1';
		}
		if (s[k + 1] == '0')
		{
			s[k + 1] = '1';
			DFS(s, step + 1);
			s[k + 1] = '0';
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	scanf("%s", Start);
	scanf("%s", End);
	res = 500;
	DFS(Start, 0);
	printf("%d\n", res);
	return 0;
}
