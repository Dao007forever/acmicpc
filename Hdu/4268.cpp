/*
 * Author: Yang Zhang
 * Created Time: Sat 08 Sep 2012 06:53:39 PM CST
 * File Name: 4268.cpp
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
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		vector<pair<int, int> > A(n), B(n);
		for (int i = 0; i < n; i++)
			scanf("%d%d", &A[i].first, &A[i].second);
		for (int i = 0; i < n; i++)
			scanf("%d%d", &B[i].first, &B[i].second);
		sort(A.begin(), A.end());
		sort(B.begin(), B.end());
		multiset<int> st;
		int ret = 0;
		for (int i = 0, j = 0; i < n; i++) {
			for (; j < n && B[j].first <= A[i].first; j++) {
				st.insert(B[j].second);
			}
			if (st.size() == 0) continue;
			multiset<int>::iterator it = st.upper_bound(A[i].second);
			if (it != st.begin()) {
				it--;
				st.erase(it);
				ret++;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}

