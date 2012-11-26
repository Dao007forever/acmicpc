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
typedef long long LL;

#define MAXN 505
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};
struct node {
	int id, x, y, h;
}p[MAXN * MAXN];
int X, Y, D;
int father[MAXN * MAXN];
map<pair<int, int>, int> mp;

bool cmp(const node &a, const node &b) {
	if (a.h == b.h) return a.id > b.id;
	return a.h > b.h;
}

int getfather(int x) {
	if (father[x] == -1) return x;
	return father[x] = getfather(father[x]);
}

bool check(int x, int y) {
	if (0 <= x && x < X && 0 <= y && y < Y) return true;
	return false;
}

void construct() {
	mp.clear();
	for (int i = 0; i < X * Y; i++)
		mp[MP(p[i].x, p[i].y)] = i;
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> X >> Y >> D;
		for (int i = 0; i < X; i++)
			for (int j = 0; j < Y; j++) {
				int h;
				cin >> h;
				int id = i * Y + j;
				p[id].id = id;
				p[id].x = i; p[id].y = j;
				p[id].h = h;
				father[id] = -1;
			}

		sort(p, p + X * Y, cmp);

		construct();

		int ret = 0;
		for (int i = 0, k = 0; i < X * Y; i++) {
			for (; k < X * Y && p[k].h > p[i].h - D; k++) {
				int x = p[k].x, y = p[k].y;
				for (int j = 0; j < 4; j++) {
					int xx = x + dx[j], yy = y + dy[j];
					if (!check(xx, yy)) continue;
					int cur = mp[MP(xx, yy)];
					node tmp = p[cur];
					if (tmp.h >= p[k].h) {
						int f1 = getfather(cur);
						int f2 = getfather(k);
						if (f1 != f2) {
							if (p[f1].h > p[f2].h) {
								father[f2] = f1;
							} else {
								father[f1] = f2;
							}
						}
					}
				}
			}
			if (p[getfather(i)].h == p[i].h) {
				ret++;
			}
		}

		cout << ret << endl;
	}
	return 0;
}
