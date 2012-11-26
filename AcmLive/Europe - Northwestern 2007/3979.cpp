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

int h, l;
vector<pair<int, int> > V[2505];

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> h >> l;

		vector<vector<int> > car(h, vector<int>(l));
		for (int i = 0; i < h; i++)
			for (int j = 0; j < l; j++) {
				cin >> car[i][j];
			}

		int ret = 0;
		for (int id = 1; id <= h * l; id++) {
			int x = -1, y = -1;
			for (int i = 0; i < h; i++)
				for (int j = 0; j < l; j++)
					if (car[i][j] == id) {
						y = i; x = j;
						break;
					}
			if (x == -1) break;
			
			ret += 5 * min(x, l - x);
			ret += 2 * 10 * y;

			rotate(car[y].begin(), car[y].begin() + x, car[y].end());
		}
		cout << ret << endl;
	}
	return 0;
}
