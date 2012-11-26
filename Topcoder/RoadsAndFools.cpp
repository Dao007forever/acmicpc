#line 2 "RoadsAndFools.cpp"
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

class RoadsAndFools
{
    public:
    string determineOrientation(int length, vector <int> frontSides) {
		int n = frontSides.size();
		vector<int> a(n), b(n);
		for (int i = 0; i < n; i++) {
			int v1 = min(frontSides[i], length - frontSides[i]);
			int v2 = max(frontSides[i], length - frontSides[i]);
			if (i == 0) a[i] = v1;
			else if (a[i - 1] < v1) a[i] = v1;
			else if (a[i - 1] < v2) a[i] = v2;
			else return string("NO SOLUTION");
		}
		for (int i = n - 1; i >= 0; i--) {
			int v1 = min(frontSides[i], length - frontSides[i]);
			int v2 = max(frontSides[i], length - frontSides[i]);
			if (i == n - 1) b[i] = v2;
			else if (b[i + 1] > v2) b[i] = v2;
			else b[i] = v1;
		}
		ostringstream oss;
		for (int i = 0; i < n; i++) {
			if (a[i] != b[i]) return string("MULTIPLE SOLUTIONS");
			if (i != 0) oss << " ";
			oss << a[i];
		}
		return oss.str();
    }



        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arr1[] = {1, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "1 2 3"; verify_case(0, Arg2, determineOrientation(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 5; int Arr1[] = {5, 2, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "MULTIPLE SOLUTIONS"; verify_case(1, Arg2, determineOrientation(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 5; int Arr1[] = {4, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "1 4"; verify_case(2, Arg2, determineOrientation(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 5; int Arr1[] = {4, 4, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "NO SOLUTION"; verify_case(3, Arg2, determineOrientation(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 5; int Arr1[] = {3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "MULTIPLE SOLUTIONS"; verify_case(4, Arg2, determineOrientation(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 10; int Arr1[] = {5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "5"; verify_case(5, Arg2, determineOrientation(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        RoadsAndFools ___test;
        for (int i = 0; i < 6; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
