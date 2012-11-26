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

int n, w;
int cnt[111111];

int main() {
	freopen("in", "r", stdin);
	while (scanf("%d%d", &n, &w)) {
		if (n == 0 && w == 0) break;
		memset(cnt, 0, sizeof(cnt));
		int N = 0;
		for (int i = 0; i < n; i++) {
			int v;
			scanf("%d", &v);
			cnt[v / w]++;
			N = max(N, v / w + 1);
		}
		int Max = 0;
		for (int i = 0; i < N; i++)
			Max = max(Max, cnt[i]);
		double ret = 0;
		for (int i = 0; i < N; i++) {
			ret += (double)cnt[i] / Max * ((double)N - 1 - i) / (double)(N - 1); 
		}
		printf("%.6lf\n", ret + 0.01);
	}
	return 0;
}
