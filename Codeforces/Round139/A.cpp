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

int p[7] = {0, 6, 5, 4, 3, 2, 1};
int main() {
	int n, x;
	cin >> n >> x;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; i++)
		cin >> a[i] >> b[i];
	bool flag = true;
	for (int i = 0; i < n; i++) {
		vector<bool> vis(7);
		vis[a[i]] = vis[p[a[i]]] = true;
		vis[b[i]] = vis[p[b[i]]] = true;
		if (vis[x] || vis[p[x]]) {
			flag = false;
			break;
		}
	}
	if (flag) puts("YES");
	else puts("NO");
	return 0;
}