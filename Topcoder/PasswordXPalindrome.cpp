#line 2 "PasswordXPalindrome.cpp"
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

class PasswordXPalindrome
{
    public:
    int minSwaps(string pas) {
		int n = pas.size();

    }




        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "levle"; int Arg1 = 1; verify_case(0, Arg1, minSwaps(Arg0)); }
	void test_case_1() { string Arg0 = "racecar"; int Arg1 = 0; verify_case(1, Arg1, minSwaps(Arg0)); }
	void test_case_2() { string Arg0 = "abcdadcb"; int Arg1 = 3; verify_case(2, Arg1, minSwaps(Arg0)); }
	void test_case_3() { string Arg0 = "msmscielciel"; int Arg1 = 5; verify_case(3, Arg1, minSwaps(Arg0)); }
	void test_case_4() { string Arg0 = "hicanyouguesstodaywriter"; int Arg1 = -1; verify_case(4, Arg1, minSwaps(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        PasswordXPalindrome ___test;
        for (int i = 0; i < 6; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
