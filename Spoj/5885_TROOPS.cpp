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

const int maxn = 1005;
struct Node {
	int C, T, S;
}p[maxn];
map<int, int> mp;
int N;

bool cmp(const Node &A, const Node &B) 
{
	return A.T < B.T;
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> N;
		for (int i = 0; i < N; i++)
			cin >> p[i].C >> p[i].T >> p[i].S;
		sort(p, p + N, cmp);
		mp.clear();

		int cnt = 0;
		for (int i = 0; i < N; i++) {
			int now = p[i].T - cnt;
			if (now >= p[i].C) {
				cnt += p[i].C;
				mp[p[i].S] += p[i].C;
			} else {
				cnt += now;
				mp[p[i].S] += now;
				p[i].C -= now;
				while (p[i].C && mp.begin()->first < p[i].S) {
					if (mp.begin()->second <= p[i].C) {
						mp[p[i].S] += mp.begin()->second;
						p[i].C -= mp.begin()->second;
						mp.erase(mp.begin());
					} else {
						mp[p[i].S] += p[i].C;
						mp.begin()->second -= p[i].C;
						p[i].C = 0;
					}
				}
			}
		}
		int ret = 0;
		for (map<int, int> :: iterator it = mp.begin(); it != mp.end(); it++)
			ret += it->first * it->second;
		cout << ret << endl;
	}
	return 0;
}
