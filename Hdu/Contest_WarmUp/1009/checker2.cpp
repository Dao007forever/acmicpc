/*
 * Author: Yang Zhang
 * Created Time: Sat 25 Aug 2012 04:58:10 PM CST
 * File Name: checker2.cpp
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
int main() {
	freopen("science.out", "r", stdin);
	freopen("ans", "w", stdout);
	while (~scanf("%d\n", &n)) {
		vector<int> p[88];
		for (int i = 0; i < n; i++) {
			int x;
			string input;
			istringstream iss;
			getline(cin, input);
			iss.str(input);
			set<int> S;
			int N = 0;
			while (iss >> x) {
				p[i].PB(x);
				N = max(N, x);
				S.insert(x);
			}
			if (S.size() != N) {
				puts("NO");
				return 0;
			}
		}
		printf("%d\n", n);
	}
	return 0;
}

