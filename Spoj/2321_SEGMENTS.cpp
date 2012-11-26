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

#define MAXN 1000
const int inf = 100000000;
int N;
vector<pair<int, int> > adj[MAXN];
long long A[MAXN], B[MAXN];
int dist[MAXN];
int nodes;

bool check(int value) {
	memset(dist, 0, sizeof(dist));
	for (int i = 0; i < nodes; i++) {
		bool relaxed = false;
		for (int p = 0; p < nodes; p++)
			for (int j = 0; j < adj[p].size(); j++) {
				int q = adj[p][j].first, tmp = dist[p] + (adj[p][j].second == inf ? value : adj[p][j].second);
				if (dist[q] > tmp) {
					dist[q] = tmp;
					relaxed = true;
				}
			}
		if (!relaxed) return false;
	}
	return true;
}

int main()
{
	freopen("in", "r", stdin);
	cin >> N;
	vector<long long> S;
	for (int i = 0; i < N; i++) {
		long long t;
		cin >> A[i] >> B[i] >> t;
		A[i] = 2 * A[i] + 1, B[i] = 2 * B[i];
		S.push_back(A[i]);
		S.push_back(B[i]);
	}
	sort(S.begin(), S.end());
	S.erase(unique(S.begin(), S.end()), S.end());
	for (int i = 0; i < N; i++) {
		A[i] = lower_bound(S.begin(), S.end(), A[i]) - S.begin();
		B[i] = lower_bound(S.begin(), S.end(), B[i]) - S.begin();
	}
	nodes = S.size();
	for (int i = 1; i < nodes; i++)
		adj[i].push_back(make_pair(i - 1, 0));
	for (int i = 0; i < N; i++)
		adj[B[i]].push_back(make_pair(A[i], -1));
	for (int i = 0; i < N; i++)
		adj[A[i]].push_back(make_pair(B[i], inf));
	int l = 1, r = N, ret;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			ret = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	cout << ret << endl;
	return 0;
}
