#line 2 "PasswordXGrid.cpp"
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

int dp[55][55];
class PasswordXGrid
{
    public:
    int minSum(vector <string> h, vector <string> v) {
		int n = h.size(), m = v[0].size();
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				if (i == 0 && j == 0) continue;
				if (i == 0) dp[0][j] = dp[0][j - 1] + h[0][j - 1] - '0';
				if (j == 0) dp[i][0] = dp[i - 1][0] + v[i - 1][0] - '0';
				if (i && j) {
					int t1 = dp[i - 1][j] + v[i - 1][j] - '0';
					int t2 = dp[i][j - 1] + h[i][j - 1] - '0';
					dp[i][j] = max(t1, t2);
				}
			}
		return dp[n - 1][m - 1];
    }



        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1","4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"32"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; verify_case(0, Arg2, minSum(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"47", "59"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"361"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 19; verify_case(1, Arg2, minSum(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"36", "23", "49"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"890", "176"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 28; verify_case(2, Arg2, minSum(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"8888585","5888585"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"58585858"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 58; verify_case(3, Arg2, minSum(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"7777777","7777777","7777777","7777777"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"44444444","44444444","44444444"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 61; verify_case(4, Arg2, minSum(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        PasswordXGrid ___test;
        for (int i = 0; i < 6; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
