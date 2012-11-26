#line 2 "AlphabetPaths.cpp"
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

string A = "ABCDEFZHIKLMNOPQRSTVX";
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int cnt[1 << 21];
int List[1100000];
int n, m;
int N;
int is[55][55];

class AlphabetPaths
{
	public:
	int Find(char c) {
		for (int i = 0; i < A.size(); i++) {
			if (c == A[i]) return i;
		}
	}
	void rec(int i, int j, int k, int used) {
		if (k == 0) {
			List[N++] = used;
		}else {
			for (int d = 0; d < 4; d++) {
				int x = i + dx[d], y = j + dy[d];
				if (x >= 0 && x < n && y >= 0 && y < m && is[x][y] >= 0 && (used >> is[x][y] & 1) == 0) {
					rec(x, y, k - 1, used | 1 << is[x][y]);
				}
			}
		}
	}
	long long count(vector <string> letterMaze) {
		n = letterMaze.size();
		m = letterMaze[0].size();
		memset(is, 0, sizeof(is));
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (letterMaze[i][j] == '.') is[i][j] = -1;
				else is[i][j] = Find(letterMaze[i][j]);
			}
		}

		long long ret = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (is[i][j] >= 0) {
					N = 0;
					rec(i, j, 10, 1 << is[i][j]);
					for (int k = 0; k < N; k++) 
						cnt[List[k]]++;
					int all = ((1 << 21) - 1) ^ (1 << is[i][j]);
					for (int k = 0; k < N; k++)
						ret += cnt[all ^ List[k]];
					for (int k = 0; k < N; k++)
						cnt[List[k]]--;
				}
			}
		}
		return ret;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"ABCDEFZHIXKLMNOPQRST",
 "...................V"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { string Arr0[] = {".................VT.",
 "....................",
 "ABCDEFZHIXKLMNOPQRS.",
 "..................S.",
 ".................VT."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { string Arr0[] = {"TBCDE.PQRSA", 
 "FZHIXKLMNOV"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 50LL; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { string Arr0[] = {"ABCDEF.",
 "V....Z.",
 "T....H.",
 "S....I.",
 "R....X.",
 "KLMNOPQ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 4LL; verify_case(3, Arg1, count(Arg0)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	AlphabetPaths ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
