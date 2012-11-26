#line 2 "PasswordXGuessing.cpp"
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

class PasswordXGuessing
{
    public:
    long long howMany(vector <string> gu) {
		int n = gu.size(), m = gu[0].size();
		LL ret = 0;
		for (int i = 0; i < m; i++) {
			string pwd = gu[0];
			for (int j = 0; j < 10; j++) {
				if (j == gu[0][i] - '0') continue;
				pwd[i] = (char)('0' + j);
				bool flag = true;
				for (int k = 1; k < n; k++)
					if (!check(pwd, gu[k])) {
						flag = false;
						break;
					}
				if (flag) ret++;
			}
		}
		return ret;
    }

	bool check(string a, string b) {
		int ret = 0;
		for (int i = 0; i < a.size(); i++)
			if (a[i] != b[i]) ret++;
		return ret == 1;
	}



        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"58", "47"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; verify_case(0, Arg1, howMany(Arg0)); }
	void test_case_1() { string Arr0[] = {"539", "540", "541"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1LL; verify_case(1, Arg1, howMany(Arg0)); }
	void test_case_2() { string Arr0[] = {"12", "34", "56", "78"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(2, Arg1, howMany(Arg0)); }
	void test_case_3() { string Arr0[] = {"2", "3", "5"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 7LL; verify_case(3, Arg1, howMany(Arg0)); }
	void test_case_4() { string Arr0[] = {"4747", "4747", "4747", "4747"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 36LL; verify_case(4, Arg1, howMany(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        PasswordXGuessing ___test;
        for (int i = 0; i < 6; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
