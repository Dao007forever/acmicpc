#line 2 "SafeReturn.cpp"
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

const int inf = 1000000;
int d[55][55];
int adj[55][55];
int cx[55], cy[55], mk[55];
class SafeReturn
{
private:
	int N;
    public:
    int minRisk(int N, vector <string> streets) {
		this->N = N;
		memset(d, 0, sizeof(d));
		int n = streets.size();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (streets[i][j] == '-') d[i][j] = inf;
				else d[i][j] = streets[i][j] - '0';

		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

		memset(adj, 0, sizeof(adj));
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (d[0][i] == d[0][j] + d[j][i])
					adj[i][j] = 1;
			}
		}

		int ret = maxMatch();
		return N - ret;
    }

	int maxMatch() {
		int ret = 0;
		memset(cx, 0, sizeof(cx));
		memset(cy, 0, sizeof(cy));
		for (int i = 1; i <= N; i++) {
			if (!cx[i]) {
				memset(mk, 0, sizeof(mk));
				ret += path(i);
			}
		}
		return ret;
	}

	int path(int u) {
		for (int i = 1; i <= N; i++) {
			if (adj[u][i] > 0 && !mk[i]) {
				mk[i] = 1;
				if (!cy[i] || path(cy[i])) {
					cx[u] = i;
					cy[i] = u;
					return 1;
				}
			}
		}
		return 0;
	}



        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; string Arr1[] = {"-234",
 "2---",
 "3---",
 "4---"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, minRisk(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; string Arr1[] = {"-12",
 "1-1",
 "21-"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(1, Arg2, minRisk(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; string Arr1[] = {"-----7",
 "--1---",
 "-1-5--",
 "--5-1-",
 "---1-3",
 "7---3-"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(2, Arg2, minRisk(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 2; string Arr1[] = {"-11",
 "1-1",
 "11-"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(3, Arg2, minRisk(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        SafeReturn ___test;
        for (int i = 0; i < 6; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
