#line 2 "Survived.cpp"
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

const double eps = 1e-8;
class Survived
{
    public:
    double minTime(int x, int y, int V, int U) {
		double a = (double)U * U - V * V, b = -2.0 * U * x, c = (double)x * x + y * y;
		if (sig(a) == 0) {
			if (sig(b) == 0) {
				return sig(c) == 0 ? 0 : -1;
			}
			return sig(-c/b) >= 0 ? -c/b : -1;
		}
		double delta = b * b - 4 * a * c;
		if (sig(delta) < 0) return -1;
		double t1 = (-b - sqrt(delta)) / (2*a);
		double t2 = (-b + sqrt(delta)) / (2*a);
		if (sig(t1) < 0 && sig(t2) < 0) return -1;
		if (sig(t1) < 0 && sig(t2) >= 0) return t2;
		if (sig(t1) >= 0 && sig(t2) < 0) return t1;
		if (sig(t1) >= 0 && sig(t2) >= 0) return min(t1, t2);
    }

	int sig(double d) {
		return (d > eps) - (d < -eps);
	}



        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 1; int Arg3 = 2; double Arg4 = 0.0; verify_case(0, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; int Arg3 = 0; double Arg4 = 1.4142135623730951; verify_case(1, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 0; int Arg3 = 1; double Arg4 = -1.0; verify_case(2, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 9; int Arg1 = 3; int Arg2 = 2; int Arg3 = 3; double Arg4 = 2.0593413823019864; verify_case(3, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; double Arg4 = 0.0; verify_case(4, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arg0 = 5; int Arg1 = 12; int Arg2 = 24; int Arg3 = 26; double Arg4 = 1.3; verify_case(5, Arg4, minTime(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        Survived ___test;
        for (int i = 0; i < 6; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
