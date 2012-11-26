/*
 * Author : Yang Zhang
 */
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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

char s[1000000];

int main()
{
	freopen("B.in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%s", s);
		int len = strlen(s), n = 0;
		for (int i = 0; i < len; i++)
		{
			if (n && s[i] == s[n - 1])
			{
				n--;
			}
			else
			{
				s[n++] = s[i];
			}
		}
		s[n]= 0;
		puts(s);
	}
	return 0;
}
