// BEGIN CUT HERE

// END CUT HERE
#line 5 "DropCoins.cpp"
#include <cstring>
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;


class DropCoins {
        public:
		int n, m;
		int map[40][40];
		int s[40][40];
        int getMinimum(vector <string> board, int K) {
            n = board.size();
			m = board[0].length();
			for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
				map[i][j] = board[i - 1][j - 1] == 'o' ? 1 : 0;
				s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + map[i][j];
			}
			int res = 10000, m1, m2, m3, m4; 
			//for (int i1 = 1, i2, j1, j2; i1 <= n; i1++) for (j1 = 1; j1 <= m; j1++)
			for (int i1 = 1; i1 <= n; i1++) for (int j1 = 1; j1 <= m; j1++)
			for (int i2 = i1; i2 <= n; i2++) for (int j2 = j1; j2 <= m; j2++) {
				int t = s[i2][j2] - s[i2][j1 - 1] - s[i1 - 1][j2] + s[i1 - 1][j1 - 1];
				if (t == K) {
					m1 = i1 - 1, m2 = n - i2, m3 = j1 - 1, m4 = m - j2;
					if (m1 > m2){ int x = m1; m1 = m2; m2 = x;}
					if (m3 > m4){ int x = m3; m3 = m4; m4 = x;}
					res = min(res, m1 * 2 + m2 + m3 * 2 + m4);
				}
			}
			if (res == 10000) 
				return -1;
			return res;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".o.."
,"oooo"
,"..o."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 2; verify_case(0, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {".....o"
,"......"
,"oooooo"
,"oooooo"
,"......"
,"o....."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; int Arg2 = 3; verify_case(1, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"...."
,".oo."
,".oo."
,"...."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = -1; verify_case(2, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"......."
,"..ooo.."
,"ooooooo"
,".oo.oo."
,"oo...oo"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; int Arg2 = 4; verify_case(3, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"................."
,".ooooooo...oooo.."
,".ooooooo..oooooo."
,".oo.......oo..oo."
,".oo.......oo..oo."
,".ooooo.....oooo.."
,".ooooooo...oooo.."
,".....ooo..oo..oo."
,"......oo..oo..oo."
,".ooooooo..oooooo."
,".oooooo....oooo.."
,"................."}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 58; int Arg2 = 6; verify_case(4, Arg2, getMinimum(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
        DropCoins ___test;
        for (int i = 0; i <= 5; i++)	
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
