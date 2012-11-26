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

int n, m;
int dp[450005], vis[5000];
vector<int> bottle;

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		memset(vis, 0, sizeof(vis));
		cin >> n >> m;
		bottle.clear();
		n *= 1000;
		int w = 1 << 30;
		while (m--) {
			int low, high;
			cin >> low >> high;
			w = min(w, low * low / (high - low));
			for (int i = low; i <= high; i++)
				if (!vis[i]) {
					vis[i] = 1;
					bottle.push_back(i);
				}
		}
		if (n > w) {
			cout << 0 << endl;
		}
		else {
			memset(dp, 0, sizeof(dp));
			dp[0] = 0;
			for (int i = 0; i < bottle.size(); i++)
				for (int j = bottle[i]; j <= n; j++)
					if (dp[j - bottle[i]] + bottle[i] > dp[j])
						dp[j] = dp[j - bottle[i]] + bottle[i];
			cout << n - dp[n] << endl;
		}
		if (Test) cout << endl;
	}
	return 0;
}
