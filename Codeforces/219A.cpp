/*
 * Author: Yang Zhang
 * Created Time: Wed 29 Aug 2012 01:48:51 PM CST
 * File Name: 219A.cpp
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

int k;
string s;
int main() {
	cin >> k >> s;
	vector<int> a(30);
	for (int i = 0; i < SZ(s); i++)
		a[s[i] - 'a']++;
	for (int i = 0; i < 26; i++)
		if (a[i] % k != 0) {
			puts("-1");
			return 0;
		}
	string ret;
	for (int i = 0; i < 26; i++)
		if (a[i]) {
			for (int j = 0; j < a[i] / k; j++)
				ret += (char)('a' + i);
		}
	for (int i = 0; i < k; i++)
		cout << ret;
	cout << endl;
	return 0;
}

