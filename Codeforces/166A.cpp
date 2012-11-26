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

struct Team {
	int p, t;
}T[55];
int N, K;

bool cmp(Team A, Team B) {
	if (A.p == B.p) return A.t < B.t;
	return A.p > B.p;
}

int main() {
	freopen("in", "r", stdin);
	cin >> N >> K;
	K--;
	for (int i = 0; i < N; i++) {
		cin >> T[i].p >> T[i].t;
	}
	sort(T, T + N, cmp);
	int pro = T[K].p, time = T[K].t;
	int ret = 1;
	for (int i = K - 1; i >= 0; i--) {
		if (T[i].p == pro && T[i].t == time) ret++;
		else break;
	}
	for (int i = K + 1; i < N; i++) {
		if (T[i].p == pro && T[i].t == time) ret++;
		else break;
	}
	cout << ret << endl;
	return 0;
}
