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
int p[2222];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> p[i];
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		int cnt = 1;
		for (int f = p[i]; f != -1; f = p[f]) {
			cnt++;
		}
		ret = max(ret, cnt);
	}
	cout << ret << endl;
	return 0;
}
