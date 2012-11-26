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

int main() {
	int n, m, a, b;
	cin >> n >> m >> a >> b;
	n--;
	a--;
	b--;
	int x = a % m, y = b % m;
	if (a / m == b / m || (x == 0 && b == n) || (x == 0 && y == m - 1)) {
		cout << 1 << endl;
		return 0;
	}
	if (a / m + 1 == b / m || x == 0 || y == m - 1 || b == n || x - 1 == y) {
		cout << 2 << endl;
		return 0;
	}
	cout << 3 << endl;
	return 0;
}
