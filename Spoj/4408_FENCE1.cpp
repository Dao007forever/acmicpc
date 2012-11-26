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

const double PI = acos(-1.0);
int L;

int main() {
	while (scanf("%d", &L) && L) {
		double ret = (double)L * L / 2 / PI;
		printf("%.2lf\n", ret);
	}
	return 0;
}
