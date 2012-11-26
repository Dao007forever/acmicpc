#line 2 "LongestSequence.cpp"
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

int g[2400][2400];
class LongestSequence {
	public:
	int maxLength(vector <int> C) {
		int l = 0, r = 2333;
		while (r - l > 1) {
			int mid = (l + r) / 2;
			if (check(mid, C)) l = mid;
			else r = mid;
		}
		if (l >= 2000) return -1;
		return l;
	}
	
	bool check(int len, vector<int> C) {
		for (int i = 0; i <= len; i++) {
			for (int j = 0; j <= len; j++) {
				g[i][j] = 0;
			}
		}
		for (int i = 0; i < C.size(); i++) {
			if (C[i] > 0) {
				for (int j = 0; j + C[i] <= len; j++)
					g[j][j + C[i]] = 1;
			}
			else {
				int now = -C[i];
				for (int j = 0; j + now <= len; j++)
					g[j + now][j] = 1;
			}
		}

		int deg[2400] = {0};
		for (int i = 0; i <= len; i++) 
			for (int j = 0; j <= len; j++)
				deg[j] += g[i][j];

		for (int i = 0; i <= len; i++) {
			int k = -1;
			for (int j = 0; j <= len; j++)
				if (deg[j] == 0) k = j;
			if (k == -1) return false;
			for (int j = 0; j <= len; j++)
				deg[j] -= g[k][j];
			deg[k] = -1;
		}
		return true;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {-2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, maxLength(Arg0)); }
	void test_case_1() { int Arr0[] = {524}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, maxLength(Arg0)); }
	void test_case_2() { int Arr0[] = {1, -1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, maxLength(Arg0)); }
	void test_case_3() { int Arr0[] = {11,-7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(3, Arg1, maxLength(Arg0)); }
	void test_case_4() { int Arr0[] = {-227,690,590,-524}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 713; verify_case(4, Arg1, maxLength(Arg0)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main() {
	LongestSequence ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
