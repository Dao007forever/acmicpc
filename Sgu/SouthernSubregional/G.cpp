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

const int maxn = 200005;
int n;

int main(int argc, char const *argv[])
{
	scanf("%d\n", &n);
	for (int i = 2; i <= n; i++) {
		char c;
		scanf("%c%c%d\n", &p[i].ch, &c, &p[i].b);
	}
	int ret = 0;
	vector<int> ans;
	set<pair<int, int> > st;
	for (int i = 2; i <= n; i++) {
		if (p[i].ch == 'd') {
			st.insert(MP(p[i].b, i));
		} else {
			if (i == n) break;
			while (st.size() >= p[i].b) {
				st.erase(st.begin());
			}
		}
	}
	for (set<pair<int, int> >::iterator it = st.begin(); it != st.end(); it++) {
		ans.PB(it->second);
		ret += it->first;
	}
	if (ans.size() < p[n].b) {
		puts("-1");
		return 0;
	}
	printf("%d\n", ret);
	sort(ans.begin(), ans.end());
	printf("%d\n", ans.size());
	for (int i = 0; i < ans.size(); i++)
		printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
	return 0;
}