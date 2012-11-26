#line 2 "TypingDistance.cpp"
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

int dist[55][55];
class TypingDistance
{
    public:
    int minDistance(string keyboard, string word) {
    	memset(dist, 0, sizeof(dist));
    	for (int i = 0; i < keyboard.size(); i++) {
    		for (int j = i + 1; j < keyboard.size(); j++) {
    			dist[keyboard[i] - 'a'][keyboard[j] - 'a'] = j - i;
    			dist[keyboard[j] - 'a'][keyboard[i] - 'a'] = j - i;
    		}
    	}
    	int ret = 0;
    	for (int i = 1; i < word.size(); i++) {
    		ret += dist[word[i] - 'a'][word[i - 1] - 'a'];
    	}
    	return ret;
    }



        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "qwertyuiop"; string Arg1 = "potter"; int Arg2 = 8; verify_case(0, Arg2, minDistance(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "tc"; string Arg1 = "tctcttccctccccttc"; int Arg2 = 9; verify_case(1, Arg2, minDistance(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "a"; string Arg1 = "aaaaaaaaaaa"; int Arg2 = 0; verify_case(2, Arg2, minDistance(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "kwadrutove"; string Arg1 = "rowerowe"; int Arg2 = 39; verify_case(3, Arg2, minDistance(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "qwertyuiopasdfghjklzxcvbnm"; string Arg1 = "topcodersingleroundmatchgoodluckhavefun"; int Arg2 = 322; verify_case(4, Arg2, minDistance(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        TypingDistance ___test;
        for (int i = 0; i < 6; i++)
        ___test.run_test(i);
        return 0;
}
// END CUT HERE
