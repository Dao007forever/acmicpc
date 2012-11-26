#line 2 "MarbleDecoration.cpp"
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

class MarbleDecoration
{
	public:
	int maxLength(int R, int G, int B)
	{
		int t1, t2, t3;
		if (R == G) t1 = 2 * R;
		else t1 = 2 * min(R, G) + 1;
		if (G == B) t2 = 2 * G;
		else t2 = 2 * min(G, B) + 1;
		if (R == B) t3 = 2 * B;
		else t3 = 2 * min(R, B) + 1;
		int res = max(t1, max(t2, t3));
		return res;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; verify_case(0, Arg3, maxLength(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 0; int Arg2 = 0; int Arg3 = 1; verify_case(1, Arg3, maxLength(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 1; int Arg2 = 2; int Arg3 = 5; verify_case(2, Arg3, maxLength(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 7; int Arg1 = 7; int Arg2 = 4; int Arg3 = 14; verify_case(3, Arg3, maxLength(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 2; int Arg1 = 3; int Arg2 = 5; int Arg3 = 7; verify_case(4, Arg3, maxLength(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arg0 = 13; int Arg1 = 13; int Arg2 = 13; int Arg3 = 26; verify_case(5, Arg3, maxLength(Arg0, Arg1, Arg2)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	MarbleDecoration ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
