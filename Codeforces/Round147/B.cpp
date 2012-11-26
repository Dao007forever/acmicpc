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

int a[55][55], b[55][55];
int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	vector<int> c(n);
	vector<int> p;
	for (int i = 0; i < n; i++) cin >> c[i];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < c[i]; j++) {
			cin >> a[i][j];
			p.PB(a[i][j]);
		}
	}
	sort(p.begin(), p.end());
	int now = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < c[i]; j++) {
			b[i][j] = p[now++];
		}
	}

	vector<pair<int, int> > ansx;
	vector<pair<int, int> > ansy;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < c[i]; j++) {
			int cur = b[i][j];
			for (int u = 0; u < n; u++) {
				for (int v = 0; v < c[u]; v++) {
					if (cur == a[u][v]) {
						if (i == u && j == v) continue;
						ansx.PB(MP(i + 1, j + 1));
						ansy.PB(MP(u + 1, v + 1));
						swap(a[i][j], a[u][v]);
					}
				}
			}
		}
	}
	cout << ansx.size() << endl;
	for (int i = 0; i < ansx.size(); i++) {
		cout << ansx[i].first << " " << ansx[i].second << " " << ansy[i].first << " " << ansy[i].second << endl;
	}
	return 0;
}