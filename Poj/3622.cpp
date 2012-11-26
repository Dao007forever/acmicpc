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

#define MAXN 100005
int n, m;
vector<pair<int, int> > cow, store;
multiset<int > st;

int main(int argc, char const *argv[])
{
	scanf("%d%d", &n, &m);
	cow.clear(); store.clear(); st.clear();
	for (int i = 0; i < n; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		cow.PB(MP(b, a));
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		store.PB(MP(b, a));
	}
	sort(cow.begin(), cow.end());
	sort(store.begin(), store.end());
	int p = m - 1;
	LL ret = 0;
	for (int i = n - 1; i >= 0; i--) {
		while (p >= 0 && store[p].first >= cow[i].first) {
			st.insert(store[p].second);
			p--;
		}
		multiset<int>::iterator it = st.lower_bound(cow[i].second);
		if (it == st.end()) {
			puts("-1");
			return 0;
		}
		ret += (LL)*it;
		st.erase(it);
	}
	cout << ret << endl;
	return 0;
}