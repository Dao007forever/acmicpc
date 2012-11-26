#line 2 "BricksN.cpp"
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

const int mod = 1000000007;
int f[55];
long long dp[55][55];
class BricksN
{
	public:
	int countStructures(int w, int h, int k)
	{
		memset(dp, 0, sizeof(dp));
		memset(f, 0, sizeof(f));
		f[0] = f[1] = 1;
		for (int i = 2; i <= w; i++)
			for (int j = min(k, i); j >= 1; j--)
				f[i] = (f[i] + f[i - j]) % mod;

		for (int i = 0; i <= w; i++)
			dp[0][i] = 1;
		for (int i = 1; i <= h; i++)
		{
			dp[i][0] = 1;
			for (int j = 1; j <= w; j++)
			{
				for (int s = 0; s < j; s++)
					dp[i][j] = (dp[i][j] + f[s] * dp[i - 1][s] % mod * dp[i][j - 1 - s]) % mod;
				dp[i][j] = (dp[i][j] + f[j] * dp[i - 1][j]) % mod;
			}
		}
		return (int)dp[h][w];
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 3; int Arg3 = 13; verify_case(0, Arg3, countStructures(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 3; int Arg3 = 83; verify_case(1, Arg3, countStructures(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 5; int Arg2 = 1; int Arg3 = 6; verify_case(2, Arg3, countStructures(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 10; int Arg2 = 3; int Arg3 = 288535435; verify_case(3, Arg3, countStructures(Arg0, Arg1, Arg2)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	BricksN ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
