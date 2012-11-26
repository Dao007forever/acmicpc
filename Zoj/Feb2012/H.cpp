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

const int maxn = 1111;
struct node {
	int x, y, h;
}p[maxn];
int len;
int N, M, C;

bool inside(node t, int x, int y, int a, int b) {
	if (x <= t.x && t.x <= x + a && y <= t.y && t.y <= y + b) return true;
	return false;
}

int main() 
{
	freopen("in", "r", stdin);
	while (scanf("%d%d%d", &N, &M, &C) != EOF) {
		len = 0;
		int a, b, h, x, y;
		while (C--) {
			scanf("%d%d%d%d%d", &a, &b, &h, &x, &y);
			int k, Max = -1;
			for (int i = 0; i < len; i++) {
				if (inside(p[i], x, y, a, b)) {
					if (p[i].h > Max) {
						Max = p[i].h;
						k = i;
					}
				}
			}
			if (Max == -1) {
				p[len].x = x; p[len].y = y; p[len].h = h;
				len++;
			} else {
				p[k].h += h; 
			}
		}

		int Max = -1;
		for (int i = 0; i < len; i++)
			if (p[i].h > Max) Max = p[i].h;
		cout << Max << endl;
	}
}
