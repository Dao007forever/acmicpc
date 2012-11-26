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

const int MAXN = 1000 + 10;
char s[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%s", s);
	stack<bool> Sta;
	char* t = s;
	while (*t)
	{
		if (*t == '<' && *(t + 1) != '/')
		{
			if (*(t + 1) == 'U')
			{
				Sta.push(0);
				t += 4;
			}
			else 
			{
				Sta.push(1);
				t += 6;
			}
		}
		else if (*t == '<')
		{
			if (*(t + 2) == 'U')
			{
				t += 5;
			}
			else 
			{
				t += 7;
			}
			Sta.pop();
		}
		else
		{
			if (Sta.empty())
			{
				putchar(*t++);
			}
			else if (Sta.top())
			{
				putchar(tolower(*t++));
			}
			else
			{
				putchar(toupper(*t++));
			}
		}
	}
	printf("\n");
	return 0;
}
