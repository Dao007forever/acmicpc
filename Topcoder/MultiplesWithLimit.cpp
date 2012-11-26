#line 2 "MultiplesWithLimit.cpp"
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

struct Node
{
	string out;
	int res;
};
bool Flag[10];
bool resflag[500000];

class MultiplesWithLimit {
	public:
	string minMultiples(int N, vector <int> forbiddenDigits) {
		for (int i = 0; i < 10; i++)
			Flag[i] = 1;
		memset(resflag, 0, sizeof(resflag));
		for (int i = 0; i < forbiddenDigits.size(); i++)
			Flag[forbiddenDigits[i]] = 0;

		bool find = false;
		Node temp, x;
		queue<Node> Q;
		for (int i = 1; i < 10; i++) {
			temp.out = '0' + i;
			temp.res = i % N;
			if (Flag[i])
				Q.push(temp);
		}
		while (!Q.empty()) {
			temp = Q.front();
			Q.pop();
			if (temp.res % N == 0) {
				find = true;
				break;
			}
			for (int i = 0; i < 10; i++) {
				if (Flag[i]) {
					x.out = temp.out;
					x.out += char(i + '0');
					x.res = temp.res * 10 + i;
					x.res %= N;
					if (!resflag[x.res])
						Q.push(x);
					resflag[x.res] = true;
				}
			}
		}
		if (find) {
			if (temp.out.size() < 9) {
				return temp.out;
			}else {
				string ans;
				int n = temp.out.size();
				for (int i = 0; i < 3; i++)
					ans += temp.out[i];
				for (int i = 0; i < 3; i++)
					ans += '.';
				for (int i = n - 3, j = 0; j < 3; i++, j++)
					ans += temp.out[i];
				ans += '(';
				char temp[1111];
				sprintf(temp, "%d", n);
				string num(temp);
				ans += num;
				ans += " digits)";
				return ans;
			}
		}
		else return "IMPOSSIBLE";
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 8; int Arr1[] = {2,3,4,5,6,7,8,9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "1000"; verify_case(0, Arg2, minMultiples(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 9; int Arr1[] = {1,3,4,5,6,7,8,9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "222...222(9 digits)"; verify_case(1, Arg2, minMultiples(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 524; int Arr1[] = {5,2,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "3668"; verify_case(2, Arg2, minMultiples(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 10000; int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "IMPOSSIBLE"; verify_case(3, Arg2, minMultiples(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1; int Arr1[] = {0,1,2,3,4,5,6,7,8,9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "IMPOSSIBLE"; verify_case(4, Arg2, minMultiples(Arg0, Arg1)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main() {
	MultiplesWithLimit ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
