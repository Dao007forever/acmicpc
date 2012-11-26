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

const int MAXN = 100005;
int n, m;
int col[MAXN];
bool vis[MAXN];
set<int> st[MAXN];

int main(int argc, char const *argv[])
{
	memset(vis, 0, sizeof(vis));
	int Max = 1;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) 
		cin >> col[i], Max = max(Max, col[i]), vis[col[i]] = true;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		if (col[a] == col[b]) continue;
		st[col[a]].insert(col[b]);
		st[col[b]].insert(col[a]);
	}
	int cnt = -1, ret = 0;
	for (int i = 1; i <= Max; i++) {
		if (!vis[i]) continue;
		int size = st[i].size();
		if (size > cnt) {
			cnt = size;
			ret = i;
		}
	}
	cout << ret << endl;
	return 0;
}