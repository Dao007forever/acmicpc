#line 2 "ReversalChain.cpp"
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

const int inf = 1000000;
class ReversalChain {
	public:
	int minReversal(string init, string goal) {
		mp.clear();
		int ret = solve(init, goal);
		if (ret == inf) ret = -1;
		return ret;
	}

	int solve(string s, string t) {
		if (s == t) return 0;
		string chg = s + "->" + t;
		if (mp.find(chg) != mp.end()) return mp[chg];
		int ret = inf;
		int len = s.size();
		if (s[0] == t[0]) update(ret, solve(s.substr(1), t.substr(1)));
		if (s[len - 1] == t[len - 1]) update(ret, solve(s.substr(0, len - 1), t.substr(0, len - 1)));
		for (int i = 0; i < len / 2; i++)
			swap(s[i], s[len - i - 1]);
		if (s[0] == t[0]) update(ret, solve(s.substr(1), t.substr(1)) + 1);
		if (s[len - 1] == t[len - 1]) update(ret, solve(s.substr(0, len - 1), t.substr(0, len - 1)) + 1);
		return mp[chg] = ret;
	}

	void update(int &a, int b) {
		if (b < a) a = b;
	}

	map<string, int> mp;

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "1100"; string Arg1 = "0110"; int Arg2 = 1; verify_case(0, Arg2, minReversal(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "111000"; string Arg1 = "101010"; int Arg2 = 2; verify_case(1, Arg2, minReversal(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "0"; string Arg1 = "1"; int Arg2 = -1; verify_case(2, Arg2, minReversal(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "10101"; string Arg1 = "10101"; int Arg2 = 0; verify_case(3, Arg2, minReversal(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "111000111000"; string Arg1 = "001100110011"; int Arg2 = 4; verify_case(4, Arg2, minReversal(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main() {
	ReversalChain ___test;
	for (int i = 0; i < 6; i++)
	 ___test.run_test(i);
}

// END CUT HERE
