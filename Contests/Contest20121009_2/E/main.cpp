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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

const double PI = acos(-1.0);
int main(int argc, char const *argv[])
{
	double a, b;
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; Test--; cas++) {
		printf("Case %d: ", cas);
		scanf("%lf%lf", &a, &b);
		if (a < b) swap(a, b);
		double c = sqrt(a * a - b * b);
		double ret = 2.0 * PI * a;
		double sum = 1.0;
		double coe = 1.0, tmpc = 1.0, tmpa = 1.0;
		for (int i = 2; i <= 100000; i += 2) {
			coe *= (double)(i - 1) * (i - 1) * c * c / i / i / a / a;
			double tmp = coe / (double)(i - 1);
			sum -= tmp;
			//cout << i << " " << sum << endl;
		}
		ret *= sum;
		printf("%.6f\n", ret);
	}
	return 0;
}