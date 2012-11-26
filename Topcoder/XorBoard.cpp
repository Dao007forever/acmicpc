#line 2 "XorBoard.cpp"
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

#define MAXN 3200
const LL mod = 555555555;
int f[MAXN][MAXN];
class XorBoard
{
    public:
    int count(int H, int W, int Rcount, int Ccount, int S) {
        for (int i = 0; i < MAXN; i++) f[i][0] = 1;
        for (int i = 1; i < MAXN; i++)
            for (int j = 1; j <= i; j++) {
                f[i][j] = (f[i - 1][j - 1] + f[i - 1][j]) % mod;
            }
        LL ret = 0;
        for (int i = 0; i <= Rcount && i <= H; i++) {
            if ((Rcount - i) % 2 == 1) continue;
            for (int j = 0; j <= Ccount && j <= W; j++) {
                if ((Ccount - j) % 2 == 1) continue;
                if (i * W + j * H - i * j * 2 != S) continue;
                int a = (Rcount - i) / 2, b = (Ccount - j) / 2;
                LL tmp = (LL)f[H][i] * f[W][j] % mod;
                tmp = (tmp * f[H + a - 1][a] % mod) * f[W + b - 1][b] % mod;
                ret = (ret + tmp) % mod;
            }
        }
        return ret;
    }



        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 2; int Arg4 = 4; int Arg5 = 4; verify_case(0, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 0; int Arg3 = 0; int Arg4 = 1; int Arg5 = 0; verify_case(1, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 20; int Arg2 = 50; int Arg3 = 40; int Arg4 = 200; int Arg5 = 333759825; verify_case(2, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 1200; int Arg1 = 1000; int Arg2 = 800; int Arg3 = 600; int Arg4 = 4000; int Arg5 = 96859710; verify_case(3, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 555; int Arg1 = 555; int Arg2 = 555; int Arg3 = 555; int Arg4 = 5550; int Arg5 = 549361755; verify_case(4, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        XorBoard ___test;
        for (int i = 0; i < 6; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
