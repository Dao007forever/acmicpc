/*
 * Author: Yang Zhang
 * Created Time: Sun 19 Aug 2012 11:38:30 AM UTC
 * File Name: 10069_KOMPICI.cpp
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
int cnt[1500];
char st[20];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", st);
		int len = strlen(st);
		int state = 0;
		for (int j = 0; j < len; j++)
			state |= (1 << (st[j] - '0'));
		cnt[state]++;
	}
	LL ret = 0;
	for (int i = 0; i < (1 << 10); i++)
		for (int j = 0; j < (1 << 10); j++)
			if (i != j && (i & j)) {
				ret += (LL)cnt[i] * cnt[j];
			}
	for (int i = 0; i < (1 << 10); i++)
		ret += cnt[i] * (cnt[i] - 1);
	cout << ret / 2 << endl;
	return 0;
}
