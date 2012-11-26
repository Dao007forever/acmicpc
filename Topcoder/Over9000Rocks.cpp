#line 2 "Over9000Rocks.cpp"
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

const int maxn = 15000000 + 5;
pair<int, int> v[70000];
class Over9000Rocks
{
        public:
        int countPossibilities(vector <int> l, vector <int> u) {
			int n = l.size(), m = 0;
			for (int i = 0; i < 1 << n; i++) {
				int Left = 0, Right = 0;
				for (int k = 0; k < n; k++)
					if (i & (1 << k)) {
						Left += l[k];
						Right += u[k];
					}
				if (Right > 9000)
					v[m++] = make_pair(max(Left, 9001), Right);
			}
			sort(v, v + m);
			int ret = 0, cur = 0;
			for (int i = 0; i < m; i++) {
				if (v[i].first <= cur) {
					ret += max(v[i].second - cur, 0);
					cur = max(cur, v[i].second);
				} else {
					ret += v[i].second - v[i].first + 1;
					cur = v[i].second;
				}
			}
			return ret;
        }



        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {9000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {9001}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(0, Arg2, countPossibilities(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {9000, 1, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {9000, 2, 20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 15; verify_case(1, Arg2, countPossibilities(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1001, 2001, 3001, 3001}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1003, 2003, 3003, 3003}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; verify_case(2, Arg2, countPossibilities(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {9000,90000,1,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {9000,90000,3,15}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 38; verify_case(3, Arg2, countPossibilities(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,4,5,6,7,8}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(4, Arg2, countPossibilities(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        Over9000Rocks ___test;
        for (int i = 0; i < 6; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
