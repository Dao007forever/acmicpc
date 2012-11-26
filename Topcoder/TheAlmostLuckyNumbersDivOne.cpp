#line 2 "TheAlmostLuckyNumbersDivOne.cpp"
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

long long Count(long long a, long long b, long long cur, bool flag)
{
	long long res = 0;
	if (cur > b) return 0;
	if (cur >= a) res++;
	res += Count(a, b, cur * 10 + 4, flag);
	res += Count(a, b, cur * 10 + 7, flag);
	if (flag)
	{
		for (int i = 0; i < 10; i++)
		{
			if (i == 0 && cur == 0) continue;
			if (i == 4 || i == 7) continue;
			res += Count(a, b, cur * 10 + i, false);
		}
	}
	return res;
}

class TheAlmostLuckyNumbersDivOne
{
	public:
	long long find(long long a, long long b)
	{
		return Count(a, b, 0, true);	
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 4LL; long long Arg1 = 7LL; long long Arg2 = 4LL; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 8LL; long long Arg1 = 19LL; long long Arg2 = 4LL; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 28LL; long long Arg1 = 33LL; long long Arg2 = 0LL; verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 12345678900LL; long long Arg1 = 98765432100LL; long long Arg2 = 91136LL; verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	TheAlmostLuckyNumbersDivOne ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
