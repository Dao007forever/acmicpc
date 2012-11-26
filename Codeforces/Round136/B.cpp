/*
 * Author: Yang Zhang
 * Created Time: Sat 01 Sep 2012 12:21:14 AM CST
 * File Name: B.cpp
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
/*
 * One dimension Binary Index Tree. Notice that the array is C[1], C[2], ..., C[N]
 */
const int MAXN = 100005;
struct BinaryIndexTree {
	int N;
	int C[MAXN];
	
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

	void update(int l, int r, int num) {
		add(r, num);
		if (l > 1) add(l - 1, -num);
	}
	
	int sum(int x) {
		int ret = 0;
		for (int i = x; i > 0; i -= lowbit(i))
			ret += C[i];
		return ret;
	}

	int qry(int l, int r) {
		if (l > 1) return sum(r) - sum(l - 1);
		return sum(r);
	}
}bit;

int N, M, a[MAXN], res[MAXN];
vector<int> q[MAXN];


struct Query {
	int l, r, id;
	void input(int i) {
		id = i;
		scanf("%d %d", &l, &r);
	}
	bool operator < (const Query &cmp) const {
		return r < cmp.r;
	}
} qry[MAXN];

void work() {
	bit.init(N);
	int cur = 1;
	for (int i = 1; i <= N; i++) {
		int ww = a[i];
		if (ww <= N) {
			q[ww].push_back(i);
			int sz = q[ww].size();
			if (sz >= ww + 1) bit.update(q[ww][sz - ww - 1] + 1, q[ww][sz - ww], 1);
			if (sz >= ww + 2) bit.update(q[ww][sz - ww - 2] + 1, q[ww][sz - ww - 1], -1);
		}
		while (cur <= M && qry[cur].r == i) {
			res[qry[cur].id] = bit.qry(qry[cur].l, qry[cur].r);
			cur++;
		}
	}
}

int main() {
	while (~scanf("%d %d", &N, &M)) {
		for (int i = 1; i <= N; i++) 
			scanf("%d", &a[i]);
		for (int i = 1; i <= M; i++)
			qry[i].input(i);
		sort(qry + 1, qry + M + 1);
		
		for (int i = 1; i <= N; i++) {
			q[i].clear();
			q[i].push_back(0);
		}
		
		work();
		for (int i = 1; i <= M; i++)
			printf("%d\n", res[i]);
	}
}

