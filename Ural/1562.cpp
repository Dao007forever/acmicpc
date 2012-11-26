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
double a, b;
int n;

int main() {
	cin >> a >> b >> n;
	for (int i = 0; i < n; i++) {
		double l = -0.5 + (double)i / n;
		double r = -0.5 + (double)(i + 1) / n;
		double v = a * a * b * PI * ((r - l) / 4 - (r * r * r - l * l * l) / 3);
		printf("%.6f\n", v);
	}
	return 0;
}
