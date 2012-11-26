#line 2 "TheLuckyBasesDivTwo.cpp"
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

class TheLuckyBasesDivTwo
{

	long long count3DorMore(long long n)
	{
		long long cnt = 0;
		for (int b = 2; b <= n; b++)
		{
			int temp = 0;
			long long x = n;
			bool luck = true;
			while (x > 0)
			{
				luck = luck && (x % b == 4 || x % b == 7);
				x /= b;
				temp++;
			}
			if (temp <= 2) break;
			if (luck) cnt++;
		}
		return cnt;
	}

	bool canDoPair(long long n, long long a, long long b)
	{
		long long ax = n - b;
		if (ax % a == 0)
		{
			long long x = ax / a;
			return (x > a && x > b);
		}
		return false;
	}

	long long count2D(long long n)
	{
		long long r = 0;
		for (int a = 4; a <= 7; a += 3)
		for (int b = 4; b <= 7; b += 3)
			r += (canDoPair(n, a, b) ? 1 : 0);
		return r;
	}

	public:
	long long find(long long n)
	{
		if (n == 4 || n == 7) return -1;
		long long res = 0;
		res += count3DorMore(n);
		res += count2D(n);

		return res;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 255LL; long long Arg1 = 1LL; verify_case(0, Arg1, find(Arg0)); }
	void test_case_1() { long long Arg0 = 4LL; long long Arg1 = -1LL; verify_case(1, Arg1, find(Arg0)); }
	void test_case_2() { long long Arg0 = 13LL; long long Arg1 = 0LL; verify_case(2, Arg1, find(Arg0)); }
	void test_case_3() { long long Arg0 = 60LL; long long Arg1 = 2LL; verify_case(3, Arg1, find(Arg0)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	TheLuckyBasesDivTwo ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
