#line 2 "SquaredSubsets.cpp"
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

const int inf = 1000000000;
class SquaredSubsets
{
	public:
		bool isNsquared(int n, int w1, int h1, int w2, int h2) {
			if (w1 > n || h1 > n) return false;
			return (n < w2 && n < h2);
		}
		bool inSide(int px, int py, int x1, int y1, int x2, int y2) {
			return (x1 <= px && px <= x2 && y1 <= py && py <= y2);
		}
	long long countSubsets(int n, vector <int> px, vector <int> py)
	{
		set<int> sx = set<int>(px.begin(), px.end());
		set<int> sy = set<int>(py.begin(), py.end());
		sx.insert(-inf); sx.insert(inf);
		sy.insert(-inf); sy.insert(inf);
		vector<int> x = vector<int>(sx.begin(), sx.end());
		vector<int> y = vector<int>(sy.begin(), sy.end());
		set<long long> ret;

		for (int x1 = 1; x1 < x.size() - 1; x1++)
			for (int y1 = 1; y1 < y.size() - 1; y1++)
				for (int x2 = x1; x2 < x.size() - 1; x2++)
					for (int y2 = y1; y2 < y.size() - 1; y2++)
						if (isNsquared(n, x[x2] - x[x1], y[y2] - y[y1], x[x2 + 1] - x[x1 - 1], y[y2 + 1] - y[y1 - 1])) {
							long long mask = 0;
							for (int k = 0; k < px.size(); k++)
								if (inSide(px[k], py[k], x[x1], y[y1], x[x2], y[y2])) mask |= 1LL << k;
							if (mask) ret.insert(mask);
						}
		return ret.size();
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arr1[] = {-5,0,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,0,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 5LL; verify_case(0, Arg3, countSubsets(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 10; int Arr1[] = {-5,0,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,0,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 5LL; verify_case(1, Arg3, countSubsets(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 100000000; int Arr1[] = {-1,-1,-1,0,1,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {-1,0,1,1,-1,0,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 21LL; verify_case(2, Arg3, countSubsets(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 5; int Arr1[] = {5,3,6,2,1,6,4,4,7,-1,-4,-7,2,-2,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,-1,8,-5,2,5,-8,8,-6,4,3,2,7,3,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 66LL; verify_case(3, Arg3, countSubsets(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 1; int Arr1[] = {-1,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 3LL; verify_case(4, Arg3, countSubsets(Arg0, Arg1, Arg2)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	SquaredSubsets ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
