#line 2 "GogoXMarisaKirisima.cpp"
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

int g[111][111];
int vis[111];
class GogoXMarisaKirisima
{
    public:
    int solve(vector <string> choices) {
		int n = choices.size();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				g[i][j] = (choices[i][j] == 'Y') || (i == j);
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					g[i][j] = g[i][j] || (g[i][k] && g[k][j]);
		if (!g[0][n - 1]) return 0;

		for (int i = 0; i < n; i++)
			vis[i] = g[0][i] && g[i][n - 1];

		int ret = 2;
		for (int i = 0; i < n; i++) {
			if (!vis[i]) continue;
			ret--;
			for (int j = 0; j < n; j++)
				if (vis[j] && choices[j][i] == 'Y')
					ret++;
		}	

		return ret;
    }



        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NYN"
,"YNY"
,"NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, solve(Arg0)); }
	void test_case_1() { string Arr0[] = {"NNY"
,"YNY"
,"YNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, solve(Arg0)); }
	void test_case_2() { string Arr0[] = {"NN"
,"NN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, solve(Arg0)); }
	void test_case_3() { string Arr0[] = {"NYNN"
,"YNYN"
										  ,"NNNY"
,"NNYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(3, Arg1, solve(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        GogoXMarisaKirisima ___test;
        for (int i = 0; i < 5; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
