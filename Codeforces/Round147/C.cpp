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

const int maxn = 1000005;
bool vis[maxn];
int sum[maxn];
int a, b, k;
bool check(int len) {
	for (int i = a; i + len - 1 <= b; i++)
		if (sum[i + len - 1] - sum[i - 1] < k) return false;
	return true;
}
int main(int argc, char const *argv[])
{
	cin >> a >> b >> k;
	vector<int> p;
	for (int i = 2; i < maxn; i++) {
		if (!vis[i]) {
			p.PB(i);
			for (int j = 2; i * j < maxn; j++)
				vis[i * j] = true;
		}
	}
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < p.size(); i++)
		vis[p[i]] = true;
	sum[0] = 0;
	for (int i = 1; i <= b; i++)
		sum[i] = sum[i - 1] + vis[i];
	int lo = 0, hi = b - a + 1, ret = -1;
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