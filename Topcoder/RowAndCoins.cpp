#line 2 "RowAndCoins.cpp"
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

int a[111];
class RowAndCoins
{
	public:
	string getWinner(string cells)
	{
		for (int i = 0; i < cells.size(); i++)
		{
			if (cells[i] == 'A') a[i] = 1;
			else a[i] = -1;
		}
		int now = a[0];
		for (int i = 1; i < cells.size(); i++)
			if (a[i] == now)
			{
				a[i] = 0;
			}
			else
			{
				now = a[i];
			}
		int sum = 0;
		for (int i = 0; i < cells.size(); i++)
			sum += a[i];
		if (sum >= 0) return "Alice";
		else return "Bob";
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ABBB"; string Arg1 = "Alice"; verify_case(0, Arg1, getWinner(Arg0)); }
	void test_case_1() { string Arg0 = "BBBB"; string Arg1 = "Bob"; verify_case(1, Arg1, getWinner(Arg0)); }
	void test_case_2() { string Arg0 = "BA"; string Arg1 = "Alice"; verify_case(2, Arg1, getWinner(Arg0)); }
	void test_case_3() { string Arg0 = "BABBABBB"; string Arg1 = "Bob"; verify_case(3, Arg1, getWinner(Arg0)); }
	void test_case_4() { string Arg0 = "ABABBBABAABBAA"; string Arg1 = "Alice"; verify_case(4, Arg1, getWinner(Arg0)); }
	void test_case_5() { string Arg0 = "BBBAAABBAAABBB"; string Arg1 = "Bob"; verify_case(5, Arg1, getWinner(Arg0)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	RowAndCoins ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
