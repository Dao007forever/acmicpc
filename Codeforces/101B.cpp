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

const int Mod = 1000000007;
int s[1000001], a[1000001];

int main()
{
	freopen("a", "r", stdin);
	int n, m;
	cin >> n >> m;
	vector<pair<int, int> > v(m);
	vector<int> e(m);
	for (int i = 0; i < m; i++)
	{
		int s, t;
		cin >> s >> t;
		v[i] = make_pair(t, s);
		e[i] = t;
	}
	sort(v.begin(), v.end());
	sort(e.begin(), e.end());

	s[0] = 0;
	for (int i = 0; i < m; i++)
	{
		int l = lower_bound(e.begin(), e.end(), v[i].second) - e.begin();
		int r = lower_bound(e.begin(), e.end(), v[i].first) - e.begin();
		a[i] = (s[r] - s[l] + (v[i].second == 0) + Mod) % Mod;
		s[i + 1] = (s[i] + a[i]) % Mod;
	}
	int res = 0, i = m - 1;
	while ((i >= 0) && (v[i].first == n))
	{
		res = (res + a[i]) % Mod;
		i--;
	}
	cout << res << endl;
	return 0;
}
