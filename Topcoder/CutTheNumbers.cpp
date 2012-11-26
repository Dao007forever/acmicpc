#line 2 "CutTheNumbers.cpp"
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

class CutTheNumbers
{
	public:
	int maximumSum(vector <string> board)
	{
		int n = board.size();
		int m = board[0].size();
		int sum1 = 0, sum2 = 0;
		for (int i = 0; i < n; i++)
		{
			char tmp[20] = {0};
			for (int j = 0; j < m; j++)
				tmp[j] = board[i][j];
			int x = atoi(tmp);
			sum1 += x;
		}
		for (int j = 0; j < m; j++)
		{
			char tmp[20] = {0};
			for (int i = 0; i < n; i++)
			{
				tmp[i] = board[i][j];
			}
			int x = atoi(tmp);
			sum2 += x;
		}

		int res = max(sum1, sum2);
		return res;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"123",
 "312"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 435; verify_case(0, Arg1, maximumSum(Arg0)); }
	void test_case_1() { string Arr0[] = {"99",
 "11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 182; verify_case(1, Arg1, maximumSum(Arg0)); }
	void test_case_2() { string Arr0[] = {"001",
 "010",
 "111",
 "100"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1131; verify_case(2, Arg1, maximumSum(Arg0)); }
	void test_case_3() { string Arr0[] = {"8"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(3, Arg1, maximumSum(Arg0)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	CutTheNumbers ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
