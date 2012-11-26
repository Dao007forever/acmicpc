#line 2 "ThreeTeleports.cpp"
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
#define abs(x) ((x) > 0 ? (x) : -(x))

const long long inf = 1LL << 40;
long long x[5][2], y[5][2];
long long g[11][11];
class ThreeTeleports
{
	public:
	long long dist(long long x1, long long y1, long long x2, long long y2)
	{
		return abs(x1 - x2) + abs(y1 - y2);
	}
	int ID(int i)
	{
		return 2 * i + 1;
	}

	int shortestDistance(int xMe, int yMe, int xHome, int yHome, vector <string> teleports)
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				g[i][j] = inf;
			}
		g[0][7] = g[7][0] = dist(xMe, yMe, xHome, yHome);
		for (int i = 0; i < 3; i++)
		{
			istringstream ss(teleports[i]);
			ss >> x[i][1] >> y[i][1] >> x[i][2] >> y[i][2];
			g[2 * i + 1][2 * i + 2] = g[2 * i + 2][2 * i + 1] = 10;
			g[0][2 * i + 1] = g[2 * i + 1][0] = dist(x[i][1], y[i][1], xMe, yMe);
			g[7][2 * i + 1] = g[2 * i + 1][7] = dist(x[i][1], y[i][1], xHome, yHome);
			g[0][2 * i + 2] = g[2 * i + 2][0] = dist(x[i][2], y[i][2], xMe, yMe);
			g[7][2 * i + 2] = g[2 * i + 2][7] = dist(x[i][2], y[i][2], xHome, yHome);
		}
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			if (i != j)
			{
				g[ID(i)][ID(j)] = g[ID(j)][ID(i)] = dist(x[i][1], y[i][1], x[j][1], y[j][1]);
				g[ID(i)][ID(j) + 1] = g[ID(j) + 1][ID(i)] = dist(x[i][1], y[i][1], x[j][2], y[j][2]);
				g[ID(i) + 1][ID(j)] = g[ID(j)][ID(i) + 1] = dist(x[i][2], y[i][2], x[j][1], y[j][1]);
				g[ID(i) + 1][ID(j) + 1] = g[ID(j) + 1][ID(i) + 1] = dist(x[i][2], y[i][2], x[j][2], y[j][2]);
			}
		for (int k = 0; k < 8; k++)
		for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (i != j && j != k && i != k)
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
		return (int)g[0][7];
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 4; int Arg3 = 5; string Arr4[] = {"1000 1001 1000 1002", "1000 1003 1000 1004", "1000 1005 1000 1006"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 3; verify_case(0, Arg5, shortestDistance(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 20; int Arg3 = 20; string Arr4[] = {"1 1 18 20", "1000 1003 1000 1004", "1000 1005 1000 1006"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 14; verify_case(1, Arg5, shortestDistance(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 20; int Arg3 = 20; string Arr4[] = {"1000 1003 1000 1004", "18 20 1 1", "1000 1005 1000 1006"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 14; verify_case(2, Arg5, shortestDistance(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 10; int Arg2 = 10000; int Arg3 = 20000; string Arr4[] = {"1000 1003 1000 1004", "3 3 10004 20002", "1000 1005 1000 1006"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 30; verify_case(3, Arg5, shortestDistance(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 3; int Arg1 = 7; int Arg2 = 10000; int Arg3 = 30000; string Arr4[] = {"3 10 5200 4900", "12212 8699 9999 30011", "12200 8701 5203 4845"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 117; verify_case(4, Arg5, shortestDistance(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_5() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 1000000000; int Arg3 = 1000000000; string Arr4[] = {"0 1 0 999999999", "1 1000000000 999999999 0", "1000000000 1 1000000000 999999999"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arg5 = 36; verify_case(5, Arg5, shortestDistance(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	ThreeTeleports ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
