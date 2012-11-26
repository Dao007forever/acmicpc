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

#define MAXN 100005
typedef long long LL;
struct Shoe {
	int price, size, id;

	Shoe(int _size = 0, int _price = 0) {
		size = _size; price = _price;
	}

	void input(int _id) {
		id = _id;
		cin >> price >> size;
	}

	bool operator == (const Shoe &P) const {
		return size == P.size && P.price == price;
	}

	bool operator < (const Shoe &P) const {
		return size < P.size || size == P.size && price < P.price;
	}
}shoe[MAXN], cust[MAXN];
LL f[MAXN][3];//f[i][0]表示第i个不卖，f[i][1]表示卖给要size-1的，f[i][2]表示卖给要size的
int buy[MAXN][3], pre[MAXN][3];

void update(LL &v, LL a, LL b, LL c, int &pos) {
	if (a >= b && a >= c) {
		v = a; pos = 0;
	} else if (b >= a && b >= c) {
		v = b; pos = 1;
	} else {
		v = c; pos = 2;
	}
}

void output(int match, int i, int pos) {
	if (i == 0) {
		cout << match << endl;
		return;
	}
	output(match + (pos != 0), i - 1, pre[i][pos]);
	if (pos) {
		cout << cust[buy[i][pos]].id << " " << shoe[i].id << endl;
	}
}

int main() {
//	freopen("in", "r", stdin);
	int n, m;
	cin >> n;
	for (int i = 1; i <= n; i++)
		shoe[i].input(i);
	sort(shoe + 1, shoe + n + 1);
	cin >> m;
	for (int i = 1; i <= m; i++)
		cust[i].input(i);
	sort(cust + 1, cust + m + 1);

	int pos;
	for (int i = 1; i <= n; i++) {
		int size = shoe[i].size, price = shoe[i].price;

		update(f[i][0], f[i - 1][0], f[i - 1][1], f[i - 1][2], pre[i][0]);

		pos = lower_bound(cust + 1, cust + m + 1, Shoe(size - 1, price)) - cust;
		if (pos <= m && cust[pos].size == size - 1) {
			if (size == shoe[i - 1].size + 1 && pos == buy[i - 1][2]) {
				if (pos < m && cust[pos + 1].size == size - 1) {
					f[i][1] = f[i][0] + price;
					pre[i][1] = pre[i][0];
					buy[i][1] = pos + 1;
				} else {
					if (f[i - 1][0] >= f[i - 1][1]) {
						f[i][1] = f[i - 1][0] + price;
						pre[i][1] = 0;
					} else {
						f[i][1] = f[i - 1][1] + price;
						pre[i][1] = 1;
					}
					buy[i][1] = pos;
				}
			} else {
				f[i][1] = f[i][0] + price;
				pre[i][1] = pre[i][0];
				buy[i][1] = pos;
			}
		}

		pos = lower_bound(cust + 1, cust + m + 1, Shoe(size, price)) - cust;
		if (pos <= m && cust[pos].size == size) {
			f[i][2] = f[i][0] + price;
			pre[i][2] = pre[i][0];
			buy[i][2] = pos;
		}
	}
	LL ret;
	update(ret, f[n][0], f[n][1], f[n][2], pos);
	cout << ret << endl;
	output(0, n, pos);
	return 0;
}
