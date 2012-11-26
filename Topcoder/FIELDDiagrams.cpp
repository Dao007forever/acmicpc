#line 2 "FIELDDiagrams.cpp"
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

LL f[31][31];
class FIELDDiagrams {
	public:
	long long countDiagrams(int fieldOrder) {
		int n = fieldOrder;
		memset(f, 0, sizeof(f));
		f[1][0] = f[1][1] = 1;
		for (int i = 2; i <= n; i++) {
			f[i][0] = 1;
			for (int j = 1; j <= i; j++)
				f[i][j] = f[i - 1][j] + f[i][j - 1];
		}
		LL ret = 0;
		for (int i = 1; i <= n; i++)
			ret += f[n][i];
		return ret;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; long long Arg1 = 4LL; verify_case(0, Arg1, countDiagrams(Arg0)); }
	void test_case_1() { int Arg0 = 3; long long Arg1 = 13LL; verify_case(1, Arg1, countDiagrams(Arg0)); }
	void test_case_2() { int Arg0 = 5; long long Arg1 = 131LL; verify_case(2, Arg1, countDiagrams(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main() {
	FIELDDiagrams ___test;
	for (int i = 0; i < 6; i++)
	 ___test.run_test(i);
}

// END CUT HERE
