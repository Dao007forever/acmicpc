#line 2 "MonsterFarm.cpp"
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

int graph[55][55];
int deg[55];
int path[55][55];
long long f[2][55];
const long long mod = 1000000007;
class MonsterFarm
{
    public:
    int numMonsters(vector <string> transforms) {
		memset(path, 0, sizeof(path));
		memset(deg, 0, sizeof(deg));
		memset(graph, 0, sizeof(graph));
		memset(f, 0, sizeof(f));
		int n = transforms.size();
		for (int i = 0; i < n; i++) {
			istringstream sin(transforms[i]);
			int x;
			while (sin >> x) {
				++deg[i];
				x--;
				graph[i][x]++;
				path[i][x] = 1;
			}
		}

		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					path[i][j] = path[i][j] || (path[i][k] && path[k][j]);

		for (int i = 0; i < n; i++)
			if (path[0][i] && deg[i] >= 2 && path[i][i])
				return -1;

		f[0][0] = 1;
		for (int step = 0; step < n; step++) {
			memset(f[1], 0, sizeof(f[1]));
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					f[1][j] = (f[1][j] + f[0][i] * graph[i][j]) % mod;
			for (int i = 0; i < n; i++)
				f[0][i] = f[1][i];
		}
		long long ret = 0;
		for (int i = 0; i < n; i++)
			ret += f[0][i];
		return (int)(ret % mod);
    }



        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, numMonsters(Arg0)); }
	void test_case_1() { string Arr0[] = {"1 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, numMonsters(Arg0)); }
	void test_case_2() { string Arr0[] = {"2", "3", "1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, numMonsters(Arg0)); }
	void test_case_3() { string Arr0[] = {"1", "3 4", "2", "2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(3, Arg1, numMonsters(Arg0)); }
	void test_case_4() { string Arr0[] = {"2 2", "3", "4 4 4", "5", "6", "7 7 7 7", "7"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 24; verify_case(4, Arg1, numMonsters(Arg0)); }
	void test_case_5() { string Arr0[] = {"2 3","5 7","2 4","5","6","4","7"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(5, Arg1, numMonsters(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        MonsterFarm ___test;
        for (int i = 0; i < 5; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
