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

int c[1111], s[1111], f[1111], g[1111];
int main(int argc, char const *argv[])
{
//	freopen("in.txt", "r", stdin);
	int n, m, x, y;
	cin >> n >> m >> x >> y;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < m; j++)
			if (s[j] == '.') {
				c[j + 1]++;
			}	
	}
	for (int i = 1; i <= m; i++) {
		s[i] = s[i - 1] + c[i];
	}

	memset(f, 63, sizeof(f));
	memset(g, 63, sizeof(g));
	f[0] = g[0] = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = x; j <= y && i - j >= 0; j++) {
			f[i] = min(f[i], g[i - j] + j * n - s[i] + s[i - j]);
			g[i] = min(g[i], f[i - j] + s[i] - s[i - j]);
		}
	}
	cout << min(f[m], g[m]) << endl;
	return 0;
}