/*
 * Author: Yang Zhang
 * Created Time: Sat 18 Aug 2012 11:53:34 AM UTC
 * File Name: A.cpp
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

int a[5];
int main() {
	cin >> a[0] >> a[1] >> a[2];
	sort(a, a + 3);
	int res = (a[0] * 2 + a[1] - 2) * (a[1] - 1) + (a[0] + a[1] -1)*(a[2]-a[1] + 1);
	cout << res << endl;
	return 0;
}

