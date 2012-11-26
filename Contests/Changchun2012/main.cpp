/*
 * Author: Yang Zhang
 * Created Time: Sat 08 Sep 2012 12:28:38 PM CST
 * File Name: main.cpp
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

int n;
struct node {
	pair<int, int> p;
	int id;
	node() {}
	node(int x, int y, int _id) {
		p = MP(x, y);
		id = _id;
	}
	bool operator < (const node &it) const {
		return p < it.p;
	}
};
vector<node> A, B;
const int maxn = 1000005;
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

int main() {
	int Test;
	scanf("%d", &Test);
	for (; Test--; ) {
		A.clear(); B.clear();
		scanf("%d", &n);
		int a, b;
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &a, &b);
			A.PB(node(a, b, 0));
		}
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &a, &b);
			B.PB(node(a, b, 0));
		}
		T.init(n);
		sort(A.begin(), A.end());
		sort(B.begin(), B.end());
		for (int i = 0; i < n; i++) {
			B[i].id = i + 1;
			T.add(i + 1, 1);
		}
		int ret = 0;
		for (int i = A.size() - 1; i >= 0; i--) {
			int l = 0, r = n - 1, k = -1;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (B[mid].p <= A[i].p) {
					k = mid;
					l = mid + 1;
				} else r = mid - 1;
			}
			if (k != -1) {
				int s = T.sum(B[k].id);
				if (s) ret++;
				T.add(B[k].id, -1);
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}

