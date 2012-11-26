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

int main(int argc, char const *argv[])
{
	int n;
	map<string, int> mp;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int k;
		cin >> k;
		vector<string> s;
		for (int j = 0; j < k; j++) {
			string a;
			cin >> a;
			s.PB(a);
		}
		for (int mask = 0; mask < 1 << k; mask++) {
			vector<string> tmp;
			for (int j = 0; j < k; j++)
				if (mask & (1 << j)) {
					tmp.PB(s[j]);
				}
			sort(tmp.begin(), tmp.end());
			string key;
			for (int j = 0; j < tmp.size(); j++) {
				key += tmp[j];
				if (j != tmp.size() - 1) key += "#";
			}
			mp[key]++;
		}
	}
	int q;
	cin >> q;
	while (q--) {
		int k;
		cin >> k;
		vector<string> s;
		while (k--) {
			string a;
			cin >> a;
			s.PB(a);
		}
		sort(s.begin(), s.end());
		string key;
		for (int j = 0; j < s.size(); j++) {
			key += s[j];
			if (j != s.size() - 1) key += "#";
		}
		if (mp.find(key) == mp.end()) {
			printf("0\n");
		} else {
			printf("%d\n", mp[key]);
		}
	}
	return 0;
}