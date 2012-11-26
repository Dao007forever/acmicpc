/*
 * Author: Yang Zhang
 * Created Time: Sun 01 Jul 2012 03:43:36 PM UTC
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

char st[11111];
int main() {
	int n;
	while (scanf("%d", &n) && n) {
		gets(st);
		for (int i = 0; i < n; i++) {
			gets(st);
			string buf;
			int n = strlen(st);
			for (int i = 0; i < n; i++) {
				if (st[i] == ' ') {
					if (buf.size()) {
						reverse(buf.begin(), buf.end());
						cout << buf;
						buf.clear();
					}
					printf(" ");
				} else {
					buf += st[i];
				}
			}
			if (buf.size()) {
				reverse(buf.begin(), buf.end());
				cout << buf;
				buf.clear();
			}
			cout << endl;
		}
	}
	return 0;
}

