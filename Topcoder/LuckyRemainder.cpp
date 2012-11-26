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

class LuckyRemainder 
{
	public:
	int getLuckyRemainder(string X) 
	{
		int res = 0;
		for (int i = 0; i < X.size(); i++)
			res += X[i] - '0';
		for (int i = 0; i < X.size() - 1; i++)
			res = (res * 2) % 9;
		return res % 9;
	}

	void run_test(string s)
	{
		cout << getLuckyRemainder(s) << endl;
	}
}; 

// BEGIN CUT HERE
int main()
{
	LuckyRemainder ___test;
	___test.run_test("24816");
	return 0;
}
// END CUT HERE
