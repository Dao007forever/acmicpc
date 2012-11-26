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

int n;
map<string, int> mp;

int main() {
	cin >> n;
	string ret;
	int Max = 0;
	for (int i = 0; i < n; i++) {
		string name, s;
		cin >> name >> s;
		mp[name]++;
		if (mp[name] > Max) {
			Max = mp[name];
			ret = name;
		}
	}
	cout << ret << " Penguin" << endl;
	return 0;
}
