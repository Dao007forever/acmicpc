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

const int MAXN = 100000 + 10;
typedef pair<int, int> PII;
int n;
PII P[MAXN];
int res[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &P[i].first);
		P[i].second = i;
	}

	sort(P, P + n);

	int Max = -1;
	for (int i = 0; i < n; i++)
	{
		res[P[i].second] = max(0, Max - P[i].second);
		Max = max(Max, P[i].second);
	}
	
	for (int i = 0; i < n; i++)
		printf("%d ", res[i] - 1);
	printf("\n");
	return 0;
}
