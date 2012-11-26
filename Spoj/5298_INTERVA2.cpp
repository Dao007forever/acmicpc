/*
 * Author : Yang Zhang
 */
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
struct BinaryIndexTree {
	int N;
	int C[maxn];
	
	void init(int N) {
		this->N = N;
		memset(C, 0, sizeof(C));
	}
	
	int lowbit(int x) {
		return x & (-x);
	}
	
	void add(int x, int num) {
		for (int i = x; i <= N; i += lowbit(i))
			C[i] += num;
	}
	
	int sum(int x) {
		int ret = 0;
		for (int i = x; i > 0; i -= lowbit(i))
			ret += C[i];
		return ret;
	}
}T;
struct Seg {
	int a, b, id;
}s[maxn];
int n;
map<pair<int, int>, int> mp;
map<int, int> pre;
vector<int> v;
int num[maxn], ans[maxn], cnt;

bool cmp(const Seg &S, const Seg &T) {
	if (S.b == T.b) return S.a > T.a;
	return S.b > T.b;
}

void prepare() {
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	int tt = 1;
	pre.clear();
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
		pre[*it] = tt++;
	for (int i = 0; i < n; i++) {
		s[i].a = pre[s[i].a];
		s[i].b = pre[s[i].b];
	}
}

int main() {
//	freopen("in.txt", "r", stdin);
	while (scanf("%d", &n) != EOF) {
		v.clear();
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &s[i].a, &s[i].b);
			s[i].id = i;
			v.PB(s[i].a); v.PB(s[i].b);
		}
		prepare();
		sort(s, s + n, cmp);
		T.init(n);
		mp.clear();
		cnt = 0;
		memset(num, 0, sizeof(num));
		for (int i = 0; i < n; i++) {
			pair<int, int> tmp = MP(s[i].a, s[i].b);
			ans[s[i].id] = T.sum(s[i].a);
			T.add(s[i].a, 1);
			if (mp.find(tmp) == mp.end()) {
				mp[tmp] = cnt++;
			} else {
				ans[s[i].id] -= num[mp[tmp]];
			}
			num[mp[tmp]]++;
		}
		for (int i = 0; i < n; i++)
			printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
	}
	return 0;
}


