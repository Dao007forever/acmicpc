#line 2 "TheLuckyGameDivTwo.cpp"
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

int sum[5000];
class TheLuckyGameDivTwo
{

	bool Check(int x)
	{
		int tot = 0;
		while (x)
		{
			int temp = x % 10;
			if (temp == 4 || temp == 7)
			{
				x /= 10;
			}
			else
			{
				tot++;
				x /= 10;
			}
		}
		return (tot == 0);
	}
	public:
	int find(int a, int b, int jLen, int bLen)
	{
		//a = 1; b = 4747; jLen = 696; bLen = 351;
		memset(sum, 0, sizeof(sum));
		for (int i = 1; i <= 5000; i++)
		{
			if (Check(i)) sum[i] = sum[i - 1] + 1;
			else sum[i] = sum[i - 1];
		}

		int Max = 0;
		for (int i = a; i + jLen - 1 <= b; i++)
		{
			int L = i, R = i + jLen - 1;
			int Min = 10000000;
			for (int j = L; j + bLen - 1 <= R; j++)
			{
				if (sum[j + bLen - 1] - sum[j - 1] < Min)
					Min = sum[j + bLen - 1] - sum[j - 1];
			}
			Max = max(Max, Min);
		}
		return Max;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 10; int Arg2 = 2; int Arg3 = 1; int Arg4 = 0; verify_case(0, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 100; int Arg2 = 100; int Arg3 = 100; int Arg4 = 6; verify_case(1, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 8; int Arg2 = 3; int Arg3 = 2; int Arg4 = 1; verify_case(2, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 1; int Arg1 = 100; int Arg2 = 75; int Arg3 = 50; int Arg4 = 2; verify_case(3, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	TheLuckyGameDivTwo ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
