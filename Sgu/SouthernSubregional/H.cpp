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

const int maxn = 4005;
int n, k;
struct Pro {
	int cnt;
	int p[maxn];
	bool operator < (const Pro &pt) const {
		return cnt > pt.cnt;
	}
}ps[maxn];

int main(int argc, char const *argv[])
{
	map<int, int> mp;
	cin >> n >> k;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		if (mp.find(a) == mp.end()) {
			mp[a] = cnt++;
		}
		int idx = mp[a];
		ps[idx].p[ps[idx].cnt++] = b;
	}
	int N = mp.size();
	sort(ps, ps + N);

	if (k > N) {
		printf("0 0\n");
		return 0;
	}
	int ret = ps[k - 1].cnt;
	vector<int> ans;
	for (int i = 0; i < N; i++) {
		if (ps[i].cnt < ret) continue;
		sort(ps[i].p, ps[i].p + ps[i].cnt);
		reverse(ps[i].p, ps[i].p + ps[i].cnt);
		int tmp = 0;
		for (int j = 0; j < ret; j++)
			tmp += ps[i].p[j];
		ans.PB(tmp);
	}
	sort(ans.begin(), ans.end());
	reverse(ans.begin(), ans.end());
	int tot = 0;
	for (int i = 0; i < k; i++)
		tot += ans[i];
	printf("%d %d\n", ret, tot);
	return 0;
}