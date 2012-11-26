#line 2 "CollectingBonuses.cpp"
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

class CollectingBonuses {
	public:
	double expectedBuy(string n, string k) {
		LL N = 0, K = 0;
		for (int i = 0; i < n.size(); i++)
			N = N * 10 + n[i] - '0';
		for (int i = 0; i < k.size(); i++)
			K = K * 10 + k[i] - '0';
		double ret = 0;
		int lim = 0;
		for (LL i = N - K + 1; i <= N; i++) {
			ret += 1.0 / i; lim++;
			if (lim == 10000000) {
				ret += log1p((N - i) / (i + 0.5));
				break;
			}
		}
		return ret * N;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "1"; string Arg1 = "1"; double Arg2 = 1.0; verify_case(0, Arg2, expectedBuy(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "2"; string Arg1 = "1"; double Arg2 = 1.0; verify_case(1, Arg2, expectedBuy(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "2"; string Arg1 = "2"; double Arg2 = 3.0; verify_case(2, Arg2, expectedBuy(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "4"; string Arg1 = "3"; double Arg2 = 4.333333333333333; verify_case(3, Arg2, expectedBuy(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main() {
	CollectingBonuses ___test;
	for (int i = 0; i < 6; i++)
	 ___test.run_test(i);
}

// END CUT HERE
