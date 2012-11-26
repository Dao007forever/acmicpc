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

char s[10];
set<string> st;
string ss;

void rotatex()
{
	char tmp;
	tmp = ss[0];
	ss[0] = ss[2];
	ss[2] = ss[1];
	ss[1] = ss[3];
	ss[3] = tmp;
}

void rotatey()
{
	char tmp;
	tmp = ss[0];
	ss[0] = ss[4];
	ss[4] = ss[1];
	ss[1] = ss[5];
	ss[5] = tmp;
}

void rotatez()
{
	char tmp;
	tmp = ss[2];
	ss[2] = ss[4];
	ss[4] = ss[3];
	ss[3] = ss[5];
	ss[5] = tmp;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%s", s);
	sort(s, s + 6);
	st.clear();
	do
	{
		ss = s;
		bool flag = 1;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					if (st.find(ss) != st.end()) flag = false;
					rotatez();
				}
				rotatey();
			}
			rotatex();
		}
		if (flag) st.insert(s);
	}while (next_permutation(s, s + 6));
	printf("%d\n", st.size());
	return 0;
}
