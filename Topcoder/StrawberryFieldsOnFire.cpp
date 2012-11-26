#line 2 "StrawberryFieldsOnFire.cpp"
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

class StrawberryFieldsOnFire
{
	public:
	int timeLimit(int w, int h, string need, vector <string> fire)
	{

	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 5; string Arg2 = "12"; string Arr3[] = {"1 4","2 2"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; verify_case(0, Arg4, timeLimit(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 5; string Arg2 = "1"; string Arr3[] = {"1 4","2 2"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 2; verify_case(1, Arg4, timeLimit(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 5; string Arg2 = "13"; string Arr3[] = {"1 4","2 2"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(2, Arg4, timeLimit(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 1000000000; int Arg1 = 1; string Arg2 = "1"; string Arr3[] = {"1 1"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 999999998; verify_case(3, Arg4, timeLimit(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 101; int Arg1 = 101; string Arg2 = "400"; string Arr3[] = {"51 51"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 49; verify_case(4, Arg4, timeLimit(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	StrawberryFieldsOnFire ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
