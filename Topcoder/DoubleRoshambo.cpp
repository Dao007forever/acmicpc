#line 2 "DoubleRoshambo.cpp"
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

const int maxn = 55;
const int inf = 0x3f3f3f3f;
int res, n;
struct KM 
{
	int E[maxn][maxn], n;		
	bool map[maxn][maxn];		
	
	bool visx[maxn], visy[maxn];
	int mate[maxn];				

	bool dfs(int idx) 
	{
		visx[idx] = true;
		for(int i = 0; i < n; i ++) 
		{
			if(map[idx][i] && !visy[i]) 
			{
				visy[i] = true;
				if(mate[i] == -1 || dfs(mate[i])) 
				{
					mate[i] = idx;
					return true;
				}
			}
		}
		return false;
	}
	int solve() 
	{
		static int lx[maxn], ly[maxn];
		int i, j;
		for(i = 0; i < n; i ++) 
		{
			ly[i] = 0;
			lx[i] = -inf;
			for(j = 0; j < n; j ++) 
			{
				lx[i] = max(lx[i], E[i][j]);
			}
		}
		while(true) 
		{
			for(i = 0; i < n; i ++) 
			{
				for(j = 0; j < n; j ++) 
				{
					map[i][j] = lx[i]+ly[j] == E[i][j];
				}
			}
			
			memset(mate, 255, sizeof(mate));
			for(i = 0; i < n; i ++) 
			{
				memset(visx, 0, sizeof(visx));
				memset(visy, 0, sizeof(visy));
				if(false == dfs(i))	break;
			}
			if(i == n) 
			{
				break;
			} 
			else 
			{		
				int ex = inf;
				for(i = 0; i < n; i ++) 
				{
					if(false == visx[i])	continue;
					for(j = 0; j < n; j ++) 
					{
						if(false == visy[j])
							ex = min(ex, lx[i] + ly[j] - E[i][j]);
					}
				}
				for(i = 0; i < n; i ++) 
				{
					if(visx[i])	lx[i] -= ex;
					if(visy[i])	ly[i] += ex;
				}
			}
		}
		int ans = 0;
		for(int i = 0; i < n; i ++) 
		{
			ans += E[mate[i]][i];
		}
		return ans;
	}
};
KM km;

int Win(char c1, char c2)
{
	if (c1 == c2) return 0;
	if (c1 == 'R' && c2 == 'S') return 1;
	if (c1 == 'S' && c2 == 'P') return 1;
	if (c1 == 'P' && c2 == 'R') return 1;
	return -1;
}
int Calc(string a, string b)
{
	if (Win(a[0], b[0]) > 0 && Win(a[1], b[1]) > 0) return 2;
	if (Win(a[0], b[0]) == 0 && Win(a[1], b[1]) > 0) return 1;
	return 0;
}
class DoubleRoshambo
{
	public:
	int maxScore(vector <string> A, vector <string> E)
	{
		res = 0;
		n = A.size();
		km.n = n;
		for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			km.E[i][j] = Calc(A[i], E[j]);
		}
		return km.solve();
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"RR"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"SS"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(0, Arg2, maxScore(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"SR", "PP"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"PR", "RS"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(1, Arg2, maxScore(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"PP", "PP", "PP", "PP"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"RR", "PR", "SS", "SP"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(2, Arg2, maxScore(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"PS", "RS", "PP", "SP", "RR", "SS", "SP"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"RP", "SP", "RR", "SR", "RS", "SP", "SS"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10; verify_case(3, Arg2, maxScore(Arg0, Arg1)); }

// END CUT HERE


};

// BEGIN CUT HERE
int main()
{
	DoubleRoshambo ___test;
	for (int i = 0; i <= 5; i++)
	___test.run_test(i);
	return 0;
}
// END CUT HERE
