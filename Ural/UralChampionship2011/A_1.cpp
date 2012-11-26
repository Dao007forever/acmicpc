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

const int MAXN = 50 + 10;
int N;
char Start[MAXN], End[MAXN];

int Search(char *s1, char *s2)
{
	if (strlen(s1) == 1) 
	{
		if (strcmp(s1, s2) == 0) return 0;
		else return 1;
	}
	int len = strlen(s1);
	int k;
	for (int i = len - 1; i >= 0; i--)
	{
		if (s1[i] != s2[i])
		{
			k = i;
			break;
		}
	}
	if (k == 0) return 0;
	char st1[MAXN] = {0}, st2[MAXN] = {0};
	for (int i = 0; i < k; i++)
	{
		st1[i] = s1[i];
		if (i == k - 1) st2[i] = '1';
		else st2[i] = '0';
	}
	return Search(st1, st2) + 1;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	scanf("%s", Start);
	scanf("%s", End);
	int len = strlen(Start);
	int res = 0;
	for (int i = len - 1; i >= 0; i--)
	if (Start[i] != End[i])
	{
		res += Search(Start, End) + 1;
		Start[i] = End[i];
	}
	printf("%d\n", res);
	return 0;
}
