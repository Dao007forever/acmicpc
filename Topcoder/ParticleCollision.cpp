#line 2 "ParticleCollision.cpp"
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

const double PI = acos(-1.0);
class ParticleCollision {
	public:
	vector <double> collision(int vx, int vy, int vz, int x0, int y0, int z0) {
		vector<double> ret;
		int a = vx * vx + vy * vy;
		int b = 2 * (vx * x0 + vy * y0);
		int c = x0 * x0 + y0 * y0 - 1;
		int delta = b * b - 4 * a * c;
		if (!a) {
			if (!c) {
				if (vz) {
					ret.PB(0); ret.PB(0); ret.PB(0);
				} else if (check(x0 - cos(PI * z0)) && check(y0 - sin(PI * z0))) {
					ret.PB(x0); ret.PB(y0); ret.PB(z0);
				}
			}
			return ret;
		}
		if (delta < 0) return ret;
		double t1 = ((-b + sqrt(delta)) / (2 * a));
		double X1 = x0 + vx * t1;
		double Y1 = y0 + vy * t1;
		double Z1 = z0 + vz * t1;
		bool flag1 = check(X1 - cos(PI * Z1)) && check(Y1 - sin(PI * Z1));
		double t2 = ((-b - sqrt(delta)) / (2 * a));
		double X2 = x0 + vx * t2;
		double Y2 = y0 + vy * t2;
		double Z2 = z0 + vz * t2;
		bool flag2 = check(X2 - cos(PI * Z2)) && check(Y2 - sin(PI * Z2));
		if (flag1 && flag2 && delta) {
			ret.PB(0); ret.PB(0); ret.PB(0);
		} else if (flag1) {
			ret.PB(X1); ret.PB(Y1); ret.PB(Z1);
		} else if (flag2) {
			ret.PB(X2); ret.PB(Y2); ret.PB(Z2);
		}
		return ret;
	}

	bool check(double d) {
		return abs(d) < 1e-9;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <double> &Expected, const vector <double> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 0; int Arg5 = 0; double Arr6[] = { }; vector <double> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(0, Arg6, collision(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 4; int Arg2 = 1; int Arg3 = -1; int Arg4 = -1; int Arg5 = 0; double Arr6[] = {0.0, 1.0, 0.5 }; vector <double> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(1, Arg6, collision(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 4; int Arg2 = 2; int Arg3 = 5; int Arg4 = 4; int Arg5 = 0; double Arr6[] = {0.0, 0.0, 0.0 }; vector <double> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(2, Arg6, collision(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_3() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 0; int Arg3 = -1; int Arg4 = 0; int Arg5 = -9; double Arr6[] = {-1.0, 0.0, -9.0 }; vector <double> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); verify_case(3, Arg6, collision(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main() {
	ParticleCollision ___test;
	for (int i = 0; i < 6; i++)
	 ___test.run_test(i);
}

// END CUT HERE
