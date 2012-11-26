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
set<string> Mi, Ma;

int main() {
	freopen("in", "r", stdin);
	cin >> n;
	for (int i = 0; i < n; i++) {
		string name;
		string state;
		int x;
		cin >> name >> state;
		if (state != "AC" && state != "CE") {
			cin >> x;
			if (Ma.find(name) == Ma.end()) {
				if (x >= 6) Ma.insert(name);
			}
			if (Mi.find(name) == Mi.end()) {
				if (x > 6) Mi.insert(name);
			}
		} else {
			if (state == "AC") {
				if (Ma.find(name) == Ma.end()) {
					Ma.insert(name);
				}
			}
		}
	}
	cout << Mi.size() << " " << Ma.size() << endl;
	return 0;
}
