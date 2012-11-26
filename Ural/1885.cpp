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

const double eps = 1e-6;
int h, t, v, x;

int sig(double d) {
	return (d > eps) - (d < -eps);
}

int main()
{
//	freopen("in", "r", stdin);
	cin >> h >> t >> v >> x;
	double ret1, ret2;
	if (x * t > h) {
		ret1 = 0;
	} else {
		ret1 = (double)(h - t * x)/ (double)(v - x);
	}
	if (x * t <= h) {
		ret2 = t;
	} else {
		ret2 = (double)h / x;
	}
	printf("%.6f %.6f\n", ret1, ret2);
	return 0;
}
