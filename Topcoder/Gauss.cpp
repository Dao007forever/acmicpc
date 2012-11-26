#line 2 "Gauss.cpp"
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

class Gauss
{
	public:
	vector <string> whichSums(string target)
	{
		long long N = 0;
		for (int i = 0; i < target.size(); i++)
			N = N * 10 + target[i] - '0';
		vector<string> ret;
		for (long long L = 2; L * L <= 2LL * N; L++)
		{
			long long A = (2 * N / L - L + 1) / 2;
			if ((2 * A + L - 1) * L == 2LL * N)
			{
				ostringstream st;
				st << "[" << A << ", " << A + L - 1 << "]";
				ret.push_back(st.str());
			}
		}
		reverse(ret.begin(), ret.end());
		return ret;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arg0 = "42"; string Arr1[] = { "[3, 9]",  "[9, 12]",  "[13, 15]" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, whichSums(Arg0)); }
	void test_case_1() { string Arg0 = "4"; string Arr1[] = { }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, whichSums(Arg0)); }
	void test_case_2() { string Arg0 = "17"; string Arr1[] = { "[8, 9]" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, whichSums(Arg0)); }
	void test_case_3() { string Arg0 = "55"; string Arr1[] = { "[1, 10]",  "[9, 13]",  "[27, 28]" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, whichSums(Arg0)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	Gauss ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
