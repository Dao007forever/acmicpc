#line 2 "AlphabetPath.cpp"
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

char a[55][55];
int flag;
int n, m;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
class AlphabetPath
{
	public:
	string doesItExist(vector <string> letterMaze)
	{
		n = letterMaze.size(), m = letterMaze[0].size();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				a[i][j] = letterMaze[i][j];

		flag = false;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (letterMaze[i][j] == 'A')
					dfs(i, j);
		if (flag) return "YES";
		else return "NO";
	}

	void dfs(int i, int j)
	{
		if (a[i][j] == 'Z')
		{
			flag = true;
			return;
		}
		for (int k = 0; k < 4; k++)
		{
			int x = i + dx[k], y = j + dy[k];
			if (x >= 0 && x < n && y >= 0 && y < m)
			{
				if (a[x][y] - a[i][j] == 1)
					dfs(x, y);
			}
		}
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(0, Arg1, doesItExist(Arg0)); }
	void test_case_1() { string Arr0[] = {"ADEHI..Z",
 "BCFGJK.Y",
 ".PONML.X",
 ".QRSTUVW"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(1, Arg1, doesItExist(Arg0)); }
	void test_case_2() { string Arr0[] = {"ACBDEFGHIJKLMNOPQRSTUVWXYZ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NO"; verify_case(2, Arg1, doesItExist(Arg0)); }
	void test_case_3() { string Arr0[] = {"ABC.......",
 "...DEFGHIJ",
 "TSRQPONMLK",
 "UVWXYZ...."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "NO"; verify_case(3, Arg1, doesItExist(Arg0)); }
	void test_case_4() { string Arr0[] = {"..............",
 "..............",
 "..............",
 "...DEFGHIJK...",
 "...C......L...",
 "...B......M...",
 "...A......N...",
 "..........O...",
 "..ZY..TSRQP...",
 "...XWVU.......",
 ".............."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YES"; verify_case(4, Arg1, doesItExist(Arg0)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	AlphabetPath ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
