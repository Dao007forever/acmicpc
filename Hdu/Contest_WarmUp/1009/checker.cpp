/*
 * Author: Yang Zhang
 * Created Time: Sat 25 Aug 2012 04:30:47 PM CST
 * File Name: checker.cpp
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
bool vis[88];
int main() {
	freopen("out", "r", stdin);
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
		bool flag = true;
		for (int j = 0; j < p[0].size() && flag; j++) {
			memset(vis, 0, sizeof(vis));
			for (int i = 0; i < n; i++)
				if (vis[p[i][j]]) {
					flag = false;
					break;
				} else vis[p[i][j]] = true;
		}
		if (flag) puts("YES");
		else puts("NO");
	}
}

