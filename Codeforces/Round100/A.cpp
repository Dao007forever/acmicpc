#include <set>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;
const double PI = acos(-1.0), eps = 1e-8;

void outputNO() {
	cout << "NO" << endl;
}

void outputYES() {
	cout << "YES" << endl;
}
int n, R, r;
int main() {
	cin >> n >> R >> r;
	if (r > R) {
		cout << "NO" << endl;
	} else if (r * 2 > R) {
		if (n == 1) outputYES();
		else outputNO();
	} else {
		double theta = asin((double)r / (R - r));
		bool res = theta * n - eps <= PI;
		if (res) outputYES();
		else outputNO();
	}
}
