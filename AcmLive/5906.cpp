/*
 * Author:  Yang Zhang
 * Created Time:  2012年08月08日 星期三 15时05分35秒
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

#define MAXN 105
int n, m;
map<string, int> name;
string s[MAXN];
double d[MAXN][MAXN], t[MAXN][MAXN];
double x[MAXN], y[MAXN];
bool fire[MAXN];

double dist(double X1, double Y1, double X2, double Y2) {
	return sqrt((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2));
}

void init() {
	name.clear();
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		cin >> s[i] >> x[i] >> y[i];
		name[s[i]] = i;
	}
	memset(d, 0, sizeof(d));
	memset(t, 0, sizeof(t));
	memset(fire, 0, sizeof(fire));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
			if (i != j) {
				d[i][j] = dist(x[i], y[i], x[j], y[j]);
				t[i][j] = 1e30;
			}
		}

	for (; m--; ) {
		string a, b, c, s1, s2, s3;
		cin >> s1 >> a >> s2 >> b >> c >> s3;
		int k = name[s1], i = name[s2], j = name[s3];
		t[i][j] = min(t[i][j], d[k][j] - d[k][i]);
		fire[i] = fire[j] = true;
	}
}

void work() {
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				t[i][j] = min(t[i][j], t[i][k] + t[k][j]);
	for (int i = 1; i <= n; i++) {
		if (t[i][i] < 0) {
			puts("IMPOSSIBLE");
			return;
		}
	}

	int cnt = 0;
	for (int i = 1; i <= n; i++)
		if (fire[i]) cnt++;

	vector<int> ans;
	for (int k = 0; k < cnt; k++) {
		vector<int> tmp;
		for (int i = 1; i <= n; i++) 
			if (fire[i]) {
				bool flag = true;
				for (int j = 1; j <= n; j++)
					if (fire[j] && t[i][j] > 0)
						flag = false;
				if (flag) {
					tmp.PB(i);
				}
			}
		if (tmp.size() == 1) {
			ans.PB(tmp[0]);
			fire[tmp[0]] = false;
		} else {
			puts("UNKNOWN");
			return;
		}
	}
	for (int i = 0; i < ans.size() - 1; i++)
		cout << s[ans[i]] << " ";
	cout << s[ans[ans.size() - 1]] << endl;
}

int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		init();
		work();
	}
	return 0;
}