#line 2 "CorrectMultiplicationTwo.cpp"
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
#define abs(x) ((x) > 0 ? (x) : -(x))
class CorrectMultiplicationTwo
{
	public:
	int getMinimum(int a, int b, int c)
	{
		int Max = 1000000;
		long long ans = 1000000000;
		for (int i = 1; i <= Max; i++)
			for (int j = 1; j <= Max; j++)
			{
				ans = min(ans, abs(i - a) + abs(j - b) + abs((long long)i * j - c));
				if (i * j > c) break;
			}
		return (int)ans;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 19; int Arg1 = 28; int Arg2 = 522; int Arg3 = 2; verify_case(0, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 30; int Arg2 = 500; int Arg3 = 11; verify_case(1, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 111; int Arg1 = 111; int Arg2 = 12321; int Arg3 = 0; verify_case(2, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 1000; int Arg1 = 100; int Arg2 = 10; int Arg3 = 1089; verify_case(3, Arg3, getMinimum(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 399; int Arg1 = 522; int Arg2 = 199999; int Arg3 = 24; verify_case(4, Arg3, getMinimum(Arg0, Arg1, Arg2)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	CorrectMultiplicationTwo ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
