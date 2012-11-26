#line 2 "EllysCheckers.cpp"
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

int dp[1 << 22];
class EllysCheckers
{
public:
	bool check(int st, int i) {
		return st & (1 << i);
	}
    string getWinner(string board) {
		int n = board.size();
		for (int mask = 0; mask < (1 << n); mask++)
			if ((mask & 1) == 0) {
				int tt = 0;
				for (int i = 1; i <= n; i++)
					if (check(mask, i)) {
						if (!check(mask, i - 1))
							tt |= (~dp[mask - (1 << i) + (1 << (i - 1))]);
						if (i >= 3 && check(mask, i - 1) && check(mask, i - 2) && !check(mask, i - 3))
							tt |= (~dp[mask - (1 << i) + (1 << (i - 3))]);
					}
				dp[mask] = tt;
			} else {
				dp[mask] = dp[mask - 1];
			}
		int ans = 0;
		for (int i = 0; i < n; i++)
			if (board[n - i - 1] == 'o') ans |= (1 << i);
		return dp[ans] ? "YES" : "NO";
    }



        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = ".o..."; string Arg1 = "YES"; verify_case(0, Arg1, getWinner(Arg0)); }
	void test_case_1() { string Arg0 = "..o..o"; string Arg1 = "YES"; verify_case(1, Arg1, getWinner(Arg0)); }
	void test_case_2() { string Arg0 = ".o...ooo..oo.."; string Arg1 = "NO"; verify_case(2, Arg1, getWinner(Arg0)); }
	void test_case_3() { string Arg0 = "......o.ooo.o......"; string Arg1 = "YES"; verify_case(3, Arg1, getWinner(Arg0)); }
	void test_case_4() { string Arg0 = ".o..o...o....o.....o"; string Arg1 = "NO"; verify_case(4, Arg1, getWinner(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        EllysCheckers ___test;
        for (int i = 0; i < 6; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
