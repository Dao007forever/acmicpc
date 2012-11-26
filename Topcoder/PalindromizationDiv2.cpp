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

class PalindromizationDiv2 
{
	bool Check(int x)
	{
		if (x < 10) return true;
		int num[10], t = 0;
		while (x > 0)
		{
			num[t++] = x % 10;
			x /= 10;
		}
		int i = 0, j = t - 1;
		while (i < j)
		{
			if (num[i] != num[j]) return false;
			i++;
			j--;
		}
		return true;
	}

	public:
	int getMinimumCost(int X) 
	{
		for (int i = 0; ; i++)
		{
			if (Check(X + i))
				return i;
			if (i <= X && Check(X - i))
				return i;
		}
	}

	void run_test(int a)
	{
		cout << getMinimumCost(a) << endl;
	}
}; 

// BEGIN CUT HERE
int main()
{
	PalindromizationDiv2 ___test;
	___test.run_test(2011);
	return 0;
}
// END CUT HERE
