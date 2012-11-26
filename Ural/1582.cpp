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

double k1, k2, k3;

int main() {
	cin >> k1 >> k2 >> k3;
	double tmp = 1.0 / k1 + 1.0 / k2 + 1.0 / k3;
	double ret = 1000.0 / tmp;
	printf("%.0f\n", ret);
	return 0;
}
