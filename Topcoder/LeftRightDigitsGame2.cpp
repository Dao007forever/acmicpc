#line 2 "LeftRightDigitsGame2.cpp"
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

class LeftRightDigitsGame2
{
    public:
    string minNumber(string digits, string lowerBound) {
    }



        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "565"; string Arg1 = "556"; string Arg2 = "556"; verify_case(0, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "565"; string Arg1 = "566"; string Arg2 = "655"; verify_case(1, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "565"; string Arg1 = "656"; string Arg2 = ""; verify_case(2, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "9876543210"; string Arg1 = "5565565565"; string Arg2 = "5678943210"; verify_case(3, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "8016352"; string Arg1 = "1000000"; string Arg2 = "1086352"; verify_case(4, Arg2, minNumber(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        LeftRightDigitsGame2 ___test;
        for (int i = 0; i < 6; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
