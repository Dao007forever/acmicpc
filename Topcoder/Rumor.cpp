#line 2 "Rumor.cpp"
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

class Rumor {
	public:
	int getMinimum(string knowledge, vector <string> graph) {
		int n = knowledge.size();
		int tell[n];
		for (int i = 0; i < n; i++) {
			tell[i] = 0;
			for (int j = 0; j < n; j++)
				if (graph[i][j] == 'Y') tell[i] |= 1 << j;
		}
		int ret = inf;
		for (int mask = 0; mask < (1 << n); mask++) {
			int knowA = 0, knowB, freshA, freshB;
			for (int i = 0; i < n; i++)
				if (knowledge[i] == 'Y') knowA |= 1 << i;
			knowB = knowA;
			freshA = knowA;
			freshB = knowB;
			for (int day = 0; ; day++) {
				if (knowA == (1 << n) - 1 && knowB == (1 << n) - 1) {
					ret = min(ret, day);
					break;
				}
				if (freshA == 0 && freshB == 0) break;
				int oldA = knowA, oldB = knowB;
				for (int i = 0; i < n; i++) {
					int tellA = freshA & (1 << i), tellB = freshB & (1 << i);
					if (!tellA && !tellB) continue;
					if (tellA && !tellB) {
						knowA |= tell[i];
						freshA ^= 1 << i;
					} else if (!tellA && tellB) {
						knowB |= tell[i];
						freshB ^= 1 << i;
					}else {
						if (mask & (1 << i)) {
							knowA |= tell[i];
							freshA ^= 1 << i;
						} else {
							knowB |= tell[i];
							freshB ^= 1 << i;
						}
					}
				}
				freshA |= knowA ^ oldA;
				freshB |= knowB ^ oldB;
			}
		}
		if (ret == inf) ret = -1;
		return ret;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "YNN"; string Arr1[] = {"NYN"
,"NNY"
,"NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "YNNY"; string Arr1[] = {"NYYN"
,"YNNY"
,"YNNY"
,"NYYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(1, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "YYYY"; string Arr1[] = {"NYNN"
,"YNYN"
,"NYNY"
,"NNYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "YYYYYN"; string Arr1[] = {"NYYYYN"
,"YNYYYN"
,"YYNYYN"
,"YYYNYN"
,"YYYYNN"
,"NNNNNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(3, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "NNNY"; string Arr1[] = {"NNNN"
,"YNNN"
,"YNNN"
,"NYYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(4, Arg2, getMinimum(Arg0, Arg1)); }
	void test_case_5() { string Arg0 =  "NNNNNNNYYY"; string Arr1[] = {"NYNNYNNYNN"
,"NNYNYNNNNY"
,"YYNNNYNNNN"
,"YNNNYNYNNN"
,"NNYNNYNNYN"
,"NNNNYNNNYY"
,"NYNYNYNNNN"
,"NNNNNNYNYY"
,"NNNYNNNYNY"
,"NYYNNNNYNN"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(5, Arg2, getMinimum(Arg0, Arg1)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main() {
	Rumor ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
