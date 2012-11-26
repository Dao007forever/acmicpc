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

const int MAXR = 1234;
const int MAXC = 5678;
char CMD[5];
int Row[MAXR + 10], Rrank[MAXR + 10];
int Col[MAXC + 10], Crank[MAXC + 10];

int main()
{
	freopen("a", "r", stdin);
	for (int i = 0; i < MAXR; i++)
		Row[i] = Rrank[i] = i;
	for (int i = 0; i < MAXC; i++)
		Col[i] = Crank[i] = i;
	while (scanf("%s", CMD) != EOF)
	{
		int a, b;
		switch (CMD[0])
		{
			case 'R':
				scanf("%d%d", &a, &b);
				a--; b--;
				swap(Row[a], Row[b]);
				Rrank[Row[a]] = a;
				Rrank[Row[b]] = b;
				break;
			case 'C':
				scanf("%d%d", &a, &b);
				a--; b--;
				swap(Col[a], Col[b]);
				Crank[Col[a]] = a;
				Crank[Col[b]] = b;
				break;
			case 'W':
				scanf("%d", &a);
				a--;
				b = a % MAXC;
				a /= MAXC;
				printf("%d %d\n", Rrank[a] + 1, Crank[b] + 1);
				break;
			case 'Q':
				scanf("%d%d", &a, &b);
				a--; b--;
				printf("%d\n", Row[a] * MAXC + Col[b] + 1);
		}
	}
	return 0;
}
