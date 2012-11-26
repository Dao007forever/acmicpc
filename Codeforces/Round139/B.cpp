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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

int main() {
	int s, k;
	cin >> s >> k;
	vector<LL> f(50);
	f[0] = 0;
	f[1] = 1;
	for (int i = 2; i < 50; i++)
		for (int j = 1; j <= k && j <= i; j++)
			f[i] += f[i - j];
	vector<int> ans;
	int t = 1;
	while (f[t] < s) t++;
	for (int i = t; i >= 0; i--)
		if (f[i] <= s) {
			ans.PB(f[i]);
			s -= f[i];
		}
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); i++)
		printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
	return 0;
}