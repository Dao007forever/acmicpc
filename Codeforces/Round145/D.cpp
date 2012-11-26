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

struct Movie {
	int like, dislike, zero;
	int least;
}p[111];
int n, m, k;
int main(int argc, char const *argv[])
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> m >> k;
	set<int> st;
	for (int i = 0; i < k; i++) {
		int x; cin >> x;
		st.insert(x);
	}
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		int num;
		cin >> num;
		while (num--) {
			int x;
			cin >> x;
			if (x == 0) {
				p[i].zero++;
				continue;
			}
			if (st.find(x) != st.end()) {
				p[i].like++;
			} else {
				p[i].dislike++;
			}
		}
		p[i].least = p[i].like + max(0, p[i].zero - (m - k - p[i].dislike));
	}
	for (int i = 0; i < n; i++) {
		int add = min(p[i].zero, k - p[i].like);
		int tmp = p[i].like + add;
		bool flag = true;
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			if (p[j].least > tmp) {
				flag = false;
				break;
			}
		}
		if (!flag) {
			puts("1");
			continue;
		}

		flag = true;
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			if (p[i].least < p[j].like + min(p[j].zero, k - p[j].like)) {
				flag = false;
			}
		}
		if (flag) {
			puts("0");
		} else {
			puts("2");
		}
	}
	return 0;
}