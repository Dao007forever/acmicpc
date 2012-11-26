/*
 * Author: Yang Zhang
 * Created Time: Thu 13 Sep 2012 02:08:43 PM CST
 * File Name: 222D.cpp
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
	int n, k;
	cin >> n >> k;
	vector<int> a(n);
	multiset<int> st;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		st.insert(x);
	}
	sort(a.begin(), a.end());
	cout << "1 ";
	for (int i = 0; i < n; i++) {
		set<int>::iterator it = st.lower_bound(k - a[i]);
		if (it != st.end())	st.erase(it);
	}
	cout << n - st.size() << endl;
	return 0;
}

