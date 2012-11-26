#line 2 "SmallBricks31.cpp"
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

int mod = 1000000007;
int up_sta;
int ways[1111][1111];
int dp[15][1111];
class SmallBricks31
{
	public:
		int w, h;
	int countWays(int w, int h)
	{
		this->w = w; this->h = h;
		memset(ways, 0, sizeof(ways));
		memset(dp, 0, sizeof(dp));
		up_sta = 1 << w;
		for (int i = 0; i < up_sta; i++)
			dfs(0, i, 0);
		dp[0][up_sta - 1] = 1;

		int ret = 0;
		for (int i = 0; i < h; i++)
		{
			for (int s = 1; s < up_sta; s++)
			if (dp[i][s] > 0)
			{
				for (int t = 0; t < up_sta; t++)
				{
					dp[i + 1][t] += (long long)dp[i][s] * ways[s][t] % mod;
					if (dp[i + 1][t] >= mod) dp[i + 1][t] -= mod;
				}
				ret += dp[i][s];
				if (ret >= mod) ret -= mod;
			}
		}
		for (int s = 1; s < up_sta; s++)
		{
			ret += dp[h][s];
			if (ret >= mod) ret -= mod;
		}
		return ret;
	}

	void dfs(int r, int f, int t) 
	{
		if (r == w)
		{
			ways[f][t]++;
			return;
		}
		int p1 = f & (1 << r), p2 = f & (1 << (r + 1)), p3 = f & (1 << (r + 2));
		dfs(r + 1, f, t);
		if (p1 > 0)
			dfs(r + 1, f, t | (1 << r));
		if (p1 > 0 && p2 > 0)
			dfs(r + 2, f, t | (1 << r) | (1 << (r + 1)));
		if (p1 > 0 && p3 > 0)
			dfs(r + 3, f, t | (1 << r) | (1 << (r + 1)) | (1 << (r + 2)));
	}


	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 3; int Arg2 = 4; verify_case(0, Arg2, countWays(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 13; verify_case(1, Arg2, countWays(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 84; verify_case(2, Arg2, countWays(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 9; int Arg2 = 132976888; verify_case(3, Arg2, countWays(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 5; int Arg1 = 5; int Arg2 = 11676046; verify_case(4, Arg2, countWays(Arg0, Arg1)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	SmallBricks31 ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
