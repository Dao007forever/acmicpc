#line 2 "MagicBoard.cpp"
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

int n, m, sx, sy;
bool mat[55][55], vis[55][55];
int deg[111];
class MagicBoard {
	public:
	string ableToUnlock(vector <string> board) {
		memset(mat, 0, sizeof(mat));
		memset(vis, 0, sizeof(vis));
		memset(deg, 0, sizeof(deg));
		n = board.size(); m = board[0].size();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				mat[i][j] = board[i][j] == '#';
				if (mat[i][j]) {
					deg[i]++;
					deg[n + j]++;
					sx = i;
					sy = j;
				}
			}
		dfs(sx, sy);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (mat[i][j] && !vis[i][j]) return "NO";

		int odd = 0;
		for (int i = 0; i < n + m; i++)
			if (deg[i] % 2 == 1) odd++;
		if (odd > 2) return "NO";
		if (odd == 2) {
			bool check = false;
			for (int i = 0; i < m; i++)
				if (deg[n + i] % 2 == 1)
					check = true;
			if (!check) return "NO";
		}
		return "YES";
	}

	void dfs(int x, int y) {
		if (!mat[x][y]) return;
		if (vis[x][y]) return;
		vis[x][y] = true;
		for (int i = 0; i < n; i++)
			dfs(i, y);
		for (int j = 0; j < m; j++)
			dfs(x, j);
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"##",
 ".#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(0, Arg1, ableToUnlock(Arg0)); }
	void test_case_1() { string Arr0[] = {"#.",
 ".#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NO"; verify_case(1, Arg1, ableToUnlock(Arg0)); }
	void test_case_2() { string Arr0[] = {"##",
 "##",
 "##"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(2, Arg1, ableToUnlock(Arg0)); }
	void test_case_3() { string Arr0[] = {"###",
 "###",
 "###"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NO"; verify_case(3, Arg1, ableToUnlock(Arg0)); }
	void test_case_4() { string Arr0[] = {"###",
 "..#",
 "###",
 "#..",
 "###"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NO"; verify_case(4, Arg1, ableToUnlock(Arg0)); }
	void test_case_5() { string Arr0[] = {"................",
 ".######..######.",
 ".######..######.",
 ".##......##..##.",
 ".##......##..##.",
 ".######..######.",
 ".######..######.",
 ".....##..##..##.",
 ".....##..##..##.",
 ".######..######.",
 ".######..######.",
 "................"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(5, Arg1, ableToUnlock(Arg0)); }
	void test_case_6() { string Arr0[] = {"#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(6, Arg1, ableToUnlock(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main() {
	MagicBoard ___test;
	for (int i = 0; i < 6; i++)
	 ___test.run_test(i);
}

// END CUT HERE
