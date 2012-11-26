#line 2 "P8XGraphBuilder.cpp"
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

int dp[111][111];
class P8XGraphBuilder
{
  public:
  int solve(vector <int> scores) {
	int n = scores.size() + 1;
	int sum = 2 * (n - 1);
	memset(dp, -1, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 1; i <= n + 1; i++) {
	  for (int j = 0; j <= 2 * i; j++) {
		for (int d = 1; d < n; d++) {
		  if (d + j <= sum && dp[i - 1][j] != -1) {
			dp[i][d + j] = max(dp[i][d + j], dp[i - 1][j] + scores[d - 1]);
		  }
		}
	  }
	}
	return dp[n][sum];
  }            
     


        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 3, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(0, Arg1, solve(Arg0)); }
	void test_case_1() { int Arr0[] = {0, 0, 0, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(1, Arg1, solve(Arg0)); }
	void test_case_2() { int Arr0[] = {1, 2, 3, 4, 5, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; verify_case(2, Arg1, solve(Arg0)); }
	void test_case_3() { int Arr0[] = {5, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 15; verify_case(3, Arg1, solve(Arg0)); }
	void test_case_4() { int Arr0[] = {1, 3, 2, 5, 3, 7, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 20; verify_case(4, Arg1, solve(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        P8XGraphBuilder ___test;
	for (int i = 0; i < 5; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
