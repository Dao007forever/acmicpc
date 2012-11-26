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

int n, x;
int a[555];

int main() {
	cin >> n >> x;
	int less = 0, gre = 0, flag = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (a[i] == x) flag++;
		if (a[i] < x) less++;
		if (a[i] > x) gre++;
	}
	sort(a, a + n);
	int ret;
	if (!flag) {
		if (less < gre) {
			ret = gre - less - 1;
		} else {
			ret = less - gre;
		}
		ret++;
	} else {
		int tmp;
		if (gre > less) {
			tmp = gre - less;
			if (flag >= tmp) ret = 0;
			else ret = tmp - flag;
		} else {
			tmp = less - gre;
			if (flag > tmp) ret = 0;
			else ret = tmp - flag + 1;
		}
	}
	cout << ret << endl;
	return 0;
}
