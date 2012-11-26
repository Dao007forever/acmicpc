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

int n;
int cnt[1111], num[1111];
int a[1111];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	int tot = 0;
	for (int i = 1; i <= n; i++) {
		if (n == 1 || a[i] != a[i - 1]) {
			tot++;
			cnt[tot] = 1;
			num[tot] = a[i];
		} else cnt[tot]++;
	}
	for (int i = 1; i <= tot; i++)
		printf("%d %d ", cnt[i], num[i]);
	return 0;
}
