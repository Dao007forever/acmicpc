#line 2 "SPartition.cpp"
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

class SPartition
{
    public:
    long long getCount(string s) {
    }



        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "oxox"; long long Arg1 = 2LL; verify_case(0, Arg1, getCount(Arg0)); }
	void test_case_1() { string Arg0 = "oooxxx"; long long Arg1 = 0LL; verify_case(1, Arg1, getCount(Arg0)); }
	void test_case_2() { string Arg0 = "xoxxox"; long long Arg1 = 4LL; verify_case(2, Arg1, getCount(Arg0)); }
	void test_case_3() { string Arg0 = "xo"; long long Arg1 = 0LL; verify_case(3, Arg1, getCount(Arg0)); }
	void test_case_4() { string Arg0 = "ooooxoox"; long long Arg1 = 8LL; verify_case(4, Arg1, getCount(Arg0)); }
	void test_case_5() { string Arg0 = "ooxxoxox"; long long Arg1 = 8LL; verify_case(5, Arg1, getCount(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        SPartition ___test;
        for (int i = 0; i < 6; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
