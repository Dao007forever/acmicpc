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

int N, M;
int len;
int vis[1000005];
vector<int> p[1000005];

int cntbit(int x)
{
	int ret = 0;
	for (int i = 0; i < len; i++)
		if (x & (1 << i)) ret++;
	return ret;
}

long long Count(int idx)
{
	int n = M - 1;
	int ret = n;
	for (int i = 1; i < (1 << len); i++) {
		int tmp = 1, cnt = cntbit(i);
		for (int j = 0; j < p[idx].size(); j++)
			if (i & (1 << j)) tmp *= p[idx][j];
		if (cnt & 1) ret -= n / tmp;
		else ret += n / tmp;
	}
	return ret;
}

int main()
{
	cin >> N >> M;
	if (N > M) {
		int t = N;
		N = M;
		M = t;
	}
	if (N == 1 && M == 1) {
		cout << 0 << endl;
		return 0;
	}
	if (N == 1) {
		cout << 1 << endl;
		return 0;
	}

	for (int i = 2; i < N; i++)
		if (!vis[i]) {
			for (int j = 2; i * j <= N; j++)
				vis[i * j] = 1;
		}
	for (int i = 2; i < N; i++)
		if (!vis[i]) {
			for (int j = 1; i * j <= N; j++)
				p[i * j].push_back(i);
		}
	long long ret = 2;
	for (int i = 1; i < N; i++) {
		if (i == 1) ret += M - 1;
		else {
			len = p[i].size();
			int tmp = Count(i);
			ret += tmp;
			//cout << tmp << endl;
		}
	}
	cout << ret << endl;
	return 0;
}
