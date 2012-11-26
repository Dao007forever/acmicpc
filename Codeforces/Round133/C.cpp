/*
 * Author: Yang Zhang
 * Created Time: Sat 18 Aug 2012 01:02:18 PM UTC
 * File Name: C.cpp
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

int n, m, k;
int main() {
	cin >> n >> m >> k;
	vector<int> ans;
	vector<int> em(n + m + 5);
	for (int i = 1; i <= n + m; i++) {
		int cnt = 0;
		if (em[i] < k) cnt = k - em[i];
		if (em[i + 1] == 0 && cnt == 0) cnt = 1;
		for (int j = i; j < i + n && j <= n + m + 1; j++)
			em[j] += cnt;
		while (cnt--) {
			ans.PB(i);
		}
	}
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); i++)
		printf("%d ", ans[i]);
	return 0;
}

