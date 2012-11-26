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

#define MAXN 100005
struct node {
	//string s, revs;
	char s[20], revs[20];
	int a;
}p[MAXN];
int N;
/*
 * One dimension Binary Index Tree. Notice that the array is C[1], C[2], ..., C[N]
 */
const int maxn = 1000005;
struct BinaryIndexTree {
	int N;
	LL C[maxn];
	
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
	
	LL sum(int x) {
		LL ret = 0;
		for (int i = x; i > 0; i -= lowbit(i))
			ret += C[i];
		return ret;
	}
}T;

bool cmprev(node A, node B) {
	//return A.revs.compare(B.revs) < 0;
	return strcmp(A.revs, B.revs) < 0;
}

bool cmp(node A, node B) {
	//return A.s.compare(B.s) < 0;
	return strcmp(A.s, B.s) < 0;
}

int main() {
	freopen("in", "r", stdin);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		//cin >> p[i].s;
		//int len = p[i].s.size();
		//for (int j = 0; j < len; j++)
		//	p[i].revs += p[i].s[len - j - 1];
		scanf("%s", p[i].s);
		int len = strlen(p[i].s);
		for (int j = 0; j < len; j++)
			p[i].revs[j] = p[i].s[len - j - 1];
	}
	sort(p + 1, p + N + 1, cmprev);
	for (int i = 1; i <= N; i++)
		p[i].a = i;
	sort(p + 1, p + N + 1, cmp);
	LL ret = 0;
	T.init(N);
	for (int i = N; i >= 1; i--) {
		ret += T.sum(p[i].a - 1);
		T.add(p[i].a, 1);
	}
	cout << ret << endl;
	return 0;
}
