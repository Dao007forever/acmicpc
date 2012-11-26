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

const int MAXN = 31;
int n;
bool constraint[MAXN][MAXN];
bool avail[MAXN];
char output[30];
char variable[30];

void init()
{
	memset(constraint, false, sizeof(constraint));
	memset(avail, true, sizeof(avail));
}

bool check_constraint(int len, int in)
{
	for (int i = 0; i < len; i++)
		if (constraint[in][output[i] - 'a'] == true) return false;
	return true;
}

void dfs(int len)
{
	if (len == n)
	{
		for (int i = 0; i < len; i++)
			printf("%c", output[i]);
		printf("\n");
		return;
	}
	for (int i = 0; i < n; i++)
	if (avail[i] && check_constraint(len, variable[i] - 'a'))
	{
		output[len] = variable[i];
		avail[i] = false;
		dfs(len + 1);
		avail[i] = true;
	}
}

int main()
{
	freopen("a", "r", stdin);
	char input[500];
	bool blank = false;
	while (gets(input))
	{
		n = 0;
		for (int i = 0; input[i]; i++)
			if (isalpha(input[i])) variable[n++] = input[i];

		sort(variable, variable + n);
		init();
		gets(input);
		char first, second;

		for (int i = 0; input[i]; i++)
		if (isalpha(input[i]))
		{
			first = input[i];
			i++;
			while (!isalpha(input[i])) i++;
			second = input[i];
			constraint[first - 'a'][second - 'a'] = true;
		}
		if (blank) printf("\n");
		blank = true;
		dfs(0);
	}
}
