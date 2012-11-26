#include <map>
#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 10;
typedef pair<int, int > PII;
priority_queue<PII> Q;
map<int, int> mp;
int ans[maxn][3], cnt;

int main() {
	freopen("in.txt", "r", stdin);
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		mp[x]++;
	}
	for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++)
		Q.push(make_pair(it->second, it->first));
	cnt = 0;
	while (Q.size() >= 3) {
		PII a = Q.top(); Q.pop();
		PII b = Q.top(); Q.pop();
		PII c = Q.top(); Q.pop();
		ans[cnt][0] = a.second;
		ans[cnt][1] = b.second;
		ans[cnt][2] = c.second;
		sort(ans[cnt], ans[cnt] + 3);
		++cnt;
		if (--a.first > 0) Q.push(a);
		if (--b.first > 0) Q.push(b);
		if (--c.first > 0) Q.push(c);
	}
	printf("%d\n", cnt);
	for (int i = 0; i < cnt; i++)
		printf("%d %d %d\n", ans[i][2], ans[i][1], ans[i][0]);
	return 0;
}
