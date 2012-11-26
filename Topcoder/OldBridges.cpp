#line 2 "OldBridges.cpp"
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

class OldBridges
{
    public:
    string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn) {
    }



        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"XOXX","OXOX","XOXO","XXOX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 1; int Arg3 = 1; int Arg4 = 2; int Arg5 = 3; int Arg6 = 1; string Arg7 = "Yes"; verify_case(0, Arg7, isPossible(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_1() { string Arr0[] = {"XOXX","OXOX","XOXO","XXOX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 2; int Arg3 = 1; int Arg4 = 1; int Arg5 = 3; int Arg6 = 1; string Arg7 = "No"; verify_case(1, Arg7, isPossible(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_2() { string Arr0[] = {"XOXO","OXOX","XOXO","OXOX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 2; int Arg3 = 1; int Arg4 = 1; int Arg5 = 3; int Arg6 = 1; string Arg7 = "Yes"; verify_case(2, Arg7, isPossible(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_3() { string Arr0[] = {"XNXO","NXOX","XOXO","OXOX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 2; int Arg3 = 1; int Arg4 = 1; int Arg5 = 3; int Arg6 = 2; string Arg7 = "No"; verify_case(3, Arg7, isPossible(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_4() { string Arr0[] = {"XOXOO","OXOXO","XOXOO","OXOXO","OOOOX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 2; int Arg3 = 2; int Arg4 = 1; int Arg5 = 3; int Arg6 = 2; string Arg7 = "Yes"; verify_case(4, Arg7, isPossible(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }
	void test_case_5() { string Arr0[] = {"XOOOX","OXOOX","OOXOX","OOOXN","XXXNX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 4; int Arg3 = 3; int Arg4 = 1; int Arg5 = 2; int Arg6 = 2; string Arg7 = "No"; verify_case(5, Arg7, isPossible(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        OldBridges ___test;
        for (int i = 0; i < 6; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
