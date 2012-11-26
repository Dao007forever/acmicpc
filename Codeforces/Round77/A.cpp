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

const int MAXN = 100 + 10;
char str[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%s", str);
	int n = strlen(str);
	int sum1 = 0, sum2 = 0, Max = 0;
	for (int i = 0; i < n; i++)
	{
		if (str[i] == '0')
		{
			sum1++;
			sum2 = 0;
		}
		if (str[i] == '1')
		{
			sum2++;
			sum1 = 0;
		}
		if (sum1 > Max) Max = sum1;
		if (sum2 > Max) Max = sum2;
	}
	if (Max >= 7) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
