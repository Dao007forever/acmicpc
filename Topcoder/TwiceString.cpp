#line 2 "TwiceString.cpp"
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

class TwiceString
{
	public:
	string getShortest(string s)
	{
		int n = s.size();
		string ans = s + s;
		for (int i = 0; i < n; i++)
		{
			string tmp = s.substr(0, n - i) + s;
			if (s.substr(n - i, i) == s.substr(0, i))
				ans = tmp;
		}
		return ans;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "aba"; string Arg1 = "ababa"; verify_case(0, Arg1, getShortest(Arg0)); }
	void test_case_1() { string Arg0 = "xxxxx"; string Arg1 = "xxxxxx"; verify_case(1, Arg1, getShortest(Arg0)); }
	void test_case_2() { string Arg0 = "topcoder"; string Arg1 = "topcodertopcoder"; verify_case(2, Arg1, getShortest(Arg0)); }
	void test_case_3() { string Arg0 = "abracadabra"; string Arg1 = "abracadabracadabra"; verify_case(3, Arg1, getShortest(Arg0)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	TwiceString ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
