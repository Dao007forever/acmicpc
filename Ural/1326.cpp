#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int inf = 1000000000;
int N, M;
int f[1 << 21];
vector<pair<int, int> > v;

int main()
{
	freopen("in.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < 1 << N; i++)
		f[i] = inf;
	f[0] = 0;
	for (int i = 0; i < N; i++) {
		int x;
		cin >> x;
		v.push_back(make_pair(x, 1 << i));
	}
	cin >> M;
	for (int i = 0; i < M; i++) {
		int p, x;
		cin >> p >> x;
		int st = 0;
		while (x--) {
			int j;
			cin >> j;
			j--;
			st |= (1 << j);
		}
		v.push_back(make_pair(p, st));
	}
	for (int i = 0; i < v.size(); i++)
		for (int s = 0; s < 1 << N; s++) {
			int news = s | v[i].second;
			f[news] = min(f[news], f[s] + v[i].first);
		}
	cin >> M;
	int finals = 0;
	while (M--) {
		int x;
		cin >> x;
		x--;
		finals |= (1 << x);
	}
	int ret = inf;
	for (int i = 0; i < 1 << N; i++)
		if ((finals & i) >= finals)
			ret = min(ret, f[i]);
	cout << ret << endl;
	return 0;
}
