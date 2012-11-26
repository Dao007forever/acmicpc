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
 
const int MAXN = 500 + 10;
const int inf = 0x3f3f3f3f;
struct SAP
{
    int cap[MAXN][MAXN], flow[MAXN][MAXN], g[MAXN][MAXN];
    int n;
    int h[MAXN], vh[MAXN], source, sink;
    void init(int n)
    {
        this->n = n;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= n; j++)
                cap[i][j] = 0;
    }
    void addCap(int i, int j, int val)
    {
        cap[i][j] += val;
    }
    int sap(const int idx, const int maxCap)
    {
        if (idx == sink)
            return maxCap;
        int l = maxCap, d, minH = n;
        for (int i = 0; i < n; i++)
        {
            if (cap[idx][i] - flow[idx][i] > 0)
            {
                if (h[idx] == h[i] + 1)
                {
                    d = sap(i, min(l, cap[idx][i] - flow[idx][i]));
                    flow[idx][i] += d;
                    flow[i][idx] -= d;
                    l -= d;
                    if (h[source] == n || l == 0) return maxCap - l;
                }
                minH = min(minH, h[i] + 1);
            }
        }
        if (l == maxCap)
        {
            vh[h[idx]]--;
            vh[minH]++;
            if (vh[h[idx]] == 0)
                h[source] = n;
            h[idx] = minH;
        }
        return maxCap - l;
    }
    int solve(int source, int sink)
    {
        if (source == sink) return inf;
        this->sink = sink;
        this->source = source;
        memset(flow, 0, sizeof(flow));
        memset(h, 0, sizeof(h));
        memset(vh, 0, sizeof(vh));
        int ans = 0;
        while (h[source] != n)
            ans += sap(source, inf);
        return ans;
    }
    bool output(int source, int sink, int m)
    {
        for (int i = 1; i <= m; i++)
            if (cap[source][i] - flow[source][i]) return false;
         return true;
    }
}sap;

int n, m;
int w[22], r[22], score[22];
vector<pair<int, int> > v;
vector<int> cnt;

int main() {
	freopen("in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> w[i];
	for (int i = 1; i <= n; i++)
		cin >> r[i];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int x;
			cin >> x;
			if (i > 1 && i < j && x) {
				v.push_back(make_pair(i, j));
				cnt.push_back(x);
			}
		}
	}
	for (int i = 1; i <= n; i++)
		if (i == 1) score[i] = w[i] + r[i];
		else score[i] = w[i];
	m = v.size();
	sap.init(n + m + 2);
	int source = 0, sink = n + m + 1;
	int sum = 0;
	for (int i = 0; i < m; i++) {
		int a = v[i].first, b = v[i].second, c = cnt[i];
		//cout << "source " << i + 1 << " " << c << endl;
		//cout << i + 1 << " " << a + m << " " << c << endl;
		//cout << i + 1 << " " << b + m << " " << c << endl;
		sap.addCap(source, i + 1, c);
		sap.addCap(i + 1, a + m, c);
		sap.addCap(i + 1, b + m, c);
		sum += c;
	}
	for (int i = 2; i <= n; i++) {
		int tmp = score[1] - score[i];
		if (tmp < 0) {
			cout << "NO" << endl;
			return 0;
		}
		sap.addCap(i + m, sink, tmp);
		//cout << i + m << " " << "sink" << " " << tmp << endl;
	}
	int ret = sap.solve(source, sink);
	if (ret == sum) puts("YES");
	else puts("NO");
	return 0;

}
