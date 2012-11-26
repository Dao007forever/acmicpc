#line 2 "TheSquareDivTwo.cpp"
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

class TheSquareDivTwo
{
	public:
	vector <string> solve(vector <string> board)
	{
		int n = board.size();
		vector<int> cnt(n, 0);
		vector<string> res(n, "");

		for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		if (board[i][j] == 'C')
			cnt[i]++;

		for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			res[i] += '.';

		for (int j = 0; j < n; j++)
		for (int i = 0; i < cnt[j]; i++)
			res[n - 1 - i][j] = 'C';

		return res;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"..",
 "C."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"..", ".C" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, solve(Arg0)); }
	void test_case_1() { string Arr0[] = {"CC",
 ".C"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"C.", "CC" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, solve(Arg0)); }
	void test_case_2() { string Arr0[] = {".C..",
 "CC.C",
 "..C.",
 "CCCC"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"...C", ".C.C", ".C.C", "CCCC" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, solve(Arg0)); }
	void test_case_3() { string Arr0[] = {"...CCC",
 "...CCC",
 "...CCC",
 "CCC...",
 "CCC...",
 "CCC..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"......", "......", "......", "CCCCCC", "CCCCCC", "CCCCCC" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, solve(Arg0)); }
	void test_case_4() { string Arr0[] = {".....C",
 "....CC",
 "...CCC",
 "..CCCC",
 ".CCCCC",
 "CCCCCC"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {".....C", "....CC", "...CCC", "..CCCC", ".CCCCC", "CCCCCC" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, solve(Arg0)); }
	void test_case_5() { string Arr0[] = {"C.C..C.C..C..C.",
 "CCC...C..CCC.C.",
 "......CC...CCCC",
 ".C..CC.C.C.C.C.",
 "C....C.C......C",
 ".....C..CCCCC.C",
 "CCC.......CCCCC",
 "..C.C..C.C...C.",
 "CCC....CCC.CC..",
 "CC.CCCC.CCCC...",
 ".C..C.CC.C.CC.C",
 "C.CCCC..CC..C.C",
 ".CCCC.CCCCCC...",
 "..C...C.CCC.CC.",
 "CCCC..CCC.C...."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"...............", "...............", "...............", "...............", "...............", ".........C..C..", ".........C.CC..", ".C....C.CCCCC.C", ".C.C.CC.CCCCCCC", "CCCC.CC.CCCCCCC", "CCCC.CCCCCCCCCC", "CCCCCCCCCCCCCCC", "CCCCCCCCCCCCCCC", "CCCCCCCCCCCCCCC", "CCCCCCCCCCCCCCC" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(5, Arg1, solve(Arg0)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	TheSquareDivTwo ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
