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

const int maxn = 5555;
struct Task {
	int s, e;
}p[maxn];
int N;

bool cmp(Task A, Task B) {
	if (A.e != B.e) return A.e < B.e;
	return A.s < B.s;
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
		scanf("%d%d", &p[i].s, &p[i].e);
	sort(p, p + N, cmp);
	int ret = 1, now = p[0].e;
	for (int i = 1; i < N; i++) {
		if (p[i].s >= now) {
			ret++;
			now = p[i].e;
		}
	}
	cout << ret << endl;
	return 0;
}
