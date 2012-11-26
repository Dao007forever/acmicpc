#line 2 "GameOfLifeDivTwo.cpp"
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

class GameOfLifeDivTwo
{
	public:
	string theSimulation(string init, int T)
	{
		int n = init.size();

		string newS;
		while (T--)
		{
			newS =init;
			for (int i = 0; i < n; i++)
			{
				if (i == 0)
				{
					if (init[n - 1] == init[1])
						newS[i] = init[1];
				}
				else if (i == n - 1)
				{
					if (init[0] == init[n - 2])
						newS[i] = init[0];
				}
				else 
				{
					if (init[i - 1] == init[i + 1])
					{
						newS[i] = init[i - 1];
					}
				}
			}
			init = newS;
		}

		return init;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "01010"; int Arg1 = 2; string Arg2 = "00000"; verify_case(0, Arg2, theSimulation(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "010101"; int Arg1 = 5; string Arg2 = "101010"; verify_case(1, Arg2, theSimulation(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "111010"; int Arg1 = 58; string Arg2 = "111111"; verify_case(2, Arg2, theSimulation(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "111111111"; int Arg1 = 511; string Arg2 = "111111111"; verify_case(3, Arg2, theSimulation(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "110010000010111110010100001001"; int Arg1 = 1000; string Arg2 = "110000000001111110000000000001"; verify_case(4, Arg2, theSimulation(Arg0, Arg1)); }
	void test_case_5() { string Arg0 = "00101110011"; int Arg1 = 0; string Arg2 = "00101110011"; verify_case(5, Arg2, theSimulation(Arg0, Arg1)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	GameOfLifeDivTwo ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
