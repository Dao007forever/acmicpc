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

const int maxn = 100005;
int n;
int a[maxn], sumP[maxn], sumN[maxn];
int cnt;

bool check(int cha) {
	int ret = n;
	for (int i = 1; i < n; i++) {
		int tmp = sumP[i] + sumN[n] - sumN[i] + cnt;
		ret = min(ret, tmp);
	}
	return ret <= cha;
}

int main(int argc, char const *argv[])
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> n;
	sumP[0] = 0; sumN[0];
	cnt = 0;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sumP[i] = sumP[i - 1];
		sumN[i] = sumN[i - 1];
		if (a[i] < 0) sumN[i]++;
		if (a[i] > 0) sumP[i]++;
		if (a[i] == 0) cnt++;
	}
	int lo = 0, hi = n, ret = 0;
	while (lo <= hi) {
		int mid = (lo + hi) >> 1;
		if (check(mid)) {
			ret = mid;
			hi = mid - 1;
		} else lo = mid + 1;
	}
	cout << ret << endl;
	return 0;
}