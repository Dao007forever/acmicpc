#line 2 "FiveHundredEleven.cpp"
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

int dp[555][55];
vector<int> c;
int n;

int dfs(int mem, int played)
{
	if (mem == 511) return 1;
	if (played == n) return 0;
	int &res = dp[mem][played];
	if (res == -1)
	{
		res = false;
		int cnt = 0;
		for (int i = 0; i < n; i++)
			if ((mem | c[i]) == mem)
			{
				cnt++;
			}
		if (cnt > played && !dfs(mem, played + 1))
			res = true;
		for (int i = 0; i < n; i++)
			if ((mem | c[i]) != mem && !dfs((mem | c[i]), played + 1))
					res = true;
	}
	return res;
}

class FiveHundredEleven
{
	public:
	string theWinner(vector <int> cards)
	{
		memset(dp, -1, sizeof(dp));
		c = cards;
		n = c.size();
		return dfs(0, 0) ? "Fox Ciel" : "Toastman";
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3, 5, 7, 9, 510}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Fox Ciel"; verify_case(0, Arg1, theWinner(Arg0)); }
	void test_case_1() { int Arr0[] = {0, 0, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Toastman"; verify_case(1, Arg1, theWinner(Arg0)); }
	void test_case_2() { int Arr0[] = {511}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Toastman"; verify_case(2, Arg1, theWinner(Arg0)); }
	void test_case_3() { int Arr0[] = {5, 58, 192, 256}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Fox Ciel"; verify_case(3, Arg1, theWinner(Arg0)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	FiveHundredEleven ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
