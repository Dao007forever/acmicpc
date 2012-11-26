/*
 * 乘法原理
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

int b, r, y;
int k;

int main() {
	cin >> b >> r >> y;
	cin >> k;
	long long ret = 1;
	while (k--) {
		char op[10];
		scanf("%s", op);
		if (*op == 'R') ret *= r;
		else if (*op == 'B') ret *= b;
		else ret *= y;
	}
	cout << ret << endl;
}
