#line 2 "Chimney.cpp"
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

class Chimney
{
	public:
	int countWays(long long n) {

	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 1LL; int Arg1 = 24; verify_case(0, Arg1, countWays(Arg0)); }
	void test_case_1() { long long Arg0 = 2LL; int Arg1 = 1088; verify_case(1, Arg1, countWays(Arg0)); }
	void test_case_2() { long long Arg0 = 5LL; int Arg1 = 110198784; verify_case(2, Arg1, countWays(Arg0)); }
	void test_case_3() { long long Arg0 = 6LL; int Arg1 = 138284509; verify_case(3, Arg1, countWays(Arg0)); }
	void test_case_4() { long long Arg0 = 100000LL; int Arg1 = 19900327; verify_case(4, Arg1, countWays(Arg0)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	Chimney ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
