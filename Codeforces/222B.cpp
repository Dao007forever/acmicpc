/*
 * Author: Yang Zhang
 * Created Time: Thu 13 Sep 2012 01:56:18 PM CST
 * File Name: 222B.cpp
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
	int n, m, q;
	cin >> n >> m >> q;
	vector<vector<int> > mat(n);
	vector<int> row(n), col(m);
	for (int i = 0; i < n; i++)
		row[i] = i;
	for (int i = 0; i < m; i++)
		col[i] = i;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x;
			scanf("%d", &x);
			mat[i].PB(x);
		}
	}

	while (q--) {
		char op[3];
		int x, y;
		scanf("%s%d%d", op, &x, &y);
		x--; y--;
		if (*op == 'c') {
			int t = col[x];
			col[x] = col[y];
			col[y] = t;
		} else if (*op == 'r') {
			int t = row[x];
			row[x] = row[y];
			row[y] = t;
		} else {
			printf("%d\n", mat[row[x]][col[y]]);
		}
	}
	return 0;
}

