/*
 * Author : Yang Zhang
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

const int maxn = 1005;
int n, nx, ny;
bool adj[maxn][maxn];
int v[maxn], r[maxn];
int Rank[maxn], mk[maxn], cx[maxn], cy[maxn];
map<int, string> mp;

int path(int u)
{
        for (int v = 1; v <= n; v++)
        {
                if (adj[u][v] > 0 && (!mk[v]))
                {
                        mk[v] = 1;
                        if (!cy[v] || path(cy[v]))
                        {
                                cx[u] = v;
                                cy[v] = u;
                                return 1;
                        }
                }
        }
        return 0;
}

int MaxMatch()
{
        int res = 0;
        memset(cx, 0, sizeof(cx));
        memset(cy, 0, sizeof(cy));
        for (int i = 1; i <= n; i++)
        {
                if (!cx[i])
                {
                        memset(mk, 0, sizeof(mk));
                        res += path(i);
                }
        }
        return res;
}

void solve() {
	for (int i = 1; i <= n; i++)
		if (r[i] <= 2) {
			for (int j = 1; j <= n; j++)
				if (r[j] > 2 && abs(Rank[i] - Rank[j]) == 2) {
					if ((v[i] == 2 || v[j] == 2)) {
							adj[i][j] = true;
					} else {
						if (v[i] != v[j])
							adj[i][j] = true;
					}
					
				}
		}
	int ret = MaxMatch();
	cout << ret << endl;
	for (int i = 1; i <= n; i++)
		if (cx[i]) {
			int a = i, b = cx[i];
			if (v[a] == 1 || v[b] == 0) swap(a, b);
			cout << mp[a] << " " << mp[b] << endl;
		}
}

int main() {
	freopen("in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		string name, s;
		cin >> name;
		mp[i] = name;
		cin >> s;
		if (s == "anything") v[i] = 2;
		else if (s == "statements") v[i] = 0;
		else v[i] = 1;
		cin >> Rank[i];
		r[i] = Rank[i] % 4 + 1;
	}

	solve();
	return 0;
} 
