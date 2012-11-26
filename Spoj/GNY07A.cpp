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

char str[100];

int main()
{
	int N, M;
	scanf("%d", &N);
	for (int c = 1; c <= N; c++)
	{
		scanf("%d %s", &M, str);
		printf("%d ", c);
		for (int i = 0; str[i]; i++)
		if (i + 1 != M)
			putchar(str[i]);
		puts("");
	}
	return 0;
}
