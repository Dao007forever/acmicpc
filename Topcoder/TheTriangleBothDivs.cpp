#line 2 "TheTriangleBothDivs.cpp"
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

class TheTriangleBothDivs
{
	public:
	string fix(string time)
	{
		const char *p = time.c_str();
		for (int i = 0; i < 24; i++)
		for (int k = 0; k < 60; k++)
		for (int t = -9; t <= 9; t++)
		{
			char buf[100];
			sprintf(buf, "%02d:%02d GMT%+d\n", (i + t + 24) % 24, k, t);
			int tmp = 0;
			for (int s = 0; s < 11; s++)
			if (buf[s] != p[s] && p[s] != '?')
				tmp = 1;
			if (tmp == 0)
			{
				sprintf(buf, "%02d:%02d", i, k);
				return buf;
			}
		}
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "17:45 GMT-4"; string Arg1 = "21:45"; verify_case(0, Arg1, fix(Arg0)); }
	void test_case_1() { string Arg0 = "16:?? GMT??"; string Arg1 = "00:00"; verify_case(1, Arg1, fix(Arg0)); }
	void test_case_2() { string Arg0 = "?1:34 GMT-9"; string Arg1 = "06:34"; verify_case(2, Arg1, fix(Arg0)); }
	void test_case_3() { string Arg0 = "??:?? GMT??"; string Arg1 = "00:00"; verify_case(3, Arg1, fix(Arg0)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	TheTriangleBothDivs ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
