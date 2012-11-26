#line 2 "MysteriousRestaurant.cpp"
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

int n, m;
int sum[55][55], least[55], Min[55];

class MysteriousRestaurant
{
	public:
	int Mon(char ch)
	{
		if (ch >= '0' && ch <= '9') return ch - '0';
		if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 10;
		if (ch >= 'a' && ch <= 'z') return ch - 'a' + 36;
	}
	int maxDays(vector <string> prices, int budget)
	{
		n = prices.size();
		m = prices[0].size();
		
		for (int k = n; k > 0; k--)
		{
			int b = budget;
			for (int d = 0; d < 7 && b >= 0; d++)
			{
				int best = 10000000;
				for (int j = 0; j < m; j++)
				{
					int sum = 0, i = d;
					while (i < k)
					{
						sum += Mon(prices[i][j]);
						i += 7;
					}
					if (sum < best) best = sum;
				}
				b -= best;
			}
			if (b >= 0) return k;
		}
		return 0;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"26", "14", "72", "39", "32", "85", "06"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; int Arg2 = 5; verify_case(0, Arg2, maxDays(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"26", "14", "72", "39", "32", "85", "06", "91"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 20; int Arg2 = 8; verify_case(1, Arg2, maxDays(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"SRM", "512"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 0; verify_case(2, Arg2, maxDays(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"Dear", "Code", "rsHa", "veFu", "nInT", "heCh", "alle", "ngeP", "hase", "andb", "ecar", "eful"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 256; int Arg2 = 10; verify_case(3, Arg2, maxDays(Arg0, Arg1)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	MysteriousRestaurant ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
