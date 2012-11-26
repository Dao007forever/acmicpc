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

int N;

long long Parse(char *s)
{
	long long res = 0;
	int len = strlen(s);
	for (int i = 0; i < len; i++, res = res << 1)
	if (s[i] == '1')
		res += 1;
	return res >> 1;
}

long long DFS(long long sta, long long end, int len)
{
	for (int i = 0; len > 0 && ((sta ^ end) & 1) == 0; sta = sta >> 1, end = end >> 1, len--, i++);
	if (len == 0) return 0;
	if (len == 1)
	{
		if ((sta ^ end) > 0) return 1;
		return 0;
	}
	return DFS(sta >> 1, 1, len - 1) + DFS(1, end >> 1, len - 1) + 1;
}

int main()
{
	freopen("a", "r", stdin);
	char s1[100], s2[100];
	scanf("%d", &N);
	scanf("%s", s1);
	scanf("%s", s2);
	long long sta = Parse(s1);
	long long end = Parse(s2);
	cout << DFS(sta, end, N) << endl;
//	printf("%d\n", DFS(sta, end, N));
}
