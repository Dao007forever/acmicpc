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

const char MARKED = '$';
const int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
const int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

set<pair<int, int> > rotate(const set<pair<int, int> > &st, int H) {
	set<pair<int, int> > ret;
	for (set<pair<int, int> >::iterator it = st.begin(); it != st.end(); it++) {
		ret.insert(MP(it->second, H - it->first - 1));
	}
	return ret;
}

set<pair<int, int> > reverse(const set<pair<int, int> > &st, int W) {
	set<pair<int, int> > ret;
	for (set<pair<int, int> >::iterator it = st.begin(); it != st.end(); it++) {
		ret.insert(MP(it->first, W - it->second - 1));
	}
	return ret;
}

struct Cluster {
	int i, j;
	int H, W;
	char index;
	set<pair<int, int> > st;

	bool same(const Cluster &c) const {
		if ((H == c.H && W == c.W) || (H == c.W && W == c.H)) {
			set<pair<int, int> > tmp(st);
			int h = H, w = W;
			for (int k = 0; k < 4; k++) {
				if (h == c.H && w == c.W && tmp == c.st) {
					return true;
				}

				tmp = rotate(tmp, h);
				swap(h, w);
			}
			tmp = reverse(tmp, w);
			for (int k = 0; k < 4; k++) {
				if (h == c.H && w == c.W && tmp == c.st) {
					return true;
				}

				tmp = rotate(tmp, h);
				swap(h, w);
			}
			return false;
		} else {
			return false;
		}
	}

	void paint(vector<string> &grid) const {
		for (set<pair<int, int> >::iterator it = st.begin(); it != st.end(); it++) {
			grid[i + it->first][j + it->second] = index;
		}
	}
};

Cluster find_cluster(vector<string> &grid, int start_i, int start_j) {
	queue<pair<int, int> > q;
	q.push(MP(start_i, start_j));
	grid[start_i][start_j] = MARKED;
	set<pair<int, int> > st;
	int h = grid.size(), w = grid[0].size();
	int top = start_i, bottom = start_i, left = start_j, right = start_j;
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		st.insert(cur);
		for (int k = 0; k < 8; k++) {
			int x = cur.first + dx[k], y = cur.second + dy[k];
			if (x >= 0 && x < h && y >= 0 && y < w && grid[x][y] == '1') {
				grid[x][y] = MARKED;
				q.push(MP(x, y));
				top = min(top, x);
				bottom = max(bottom, x);
				left = min(left, y);
				right = max(right, y);
			}
		}
	}
	Cluster c;
	c.i = top;
	c.j = left;
	c.H = bottom - top + 1;
	c.W = right - left + 1;
	for (set<pair<int, int> >::iterator it = st.begin(); it != st.end(); it++)
		c.st.insert(MP(it->first - c.i, it->second - c.j));
	return c;
}

int main(int argc, char const *argv[])
{
	freopen("in.txt", "r", stdin);
	int W, H;
	cin >> W >> H;
	vector<string> grid(H);
	vector<Cluster> vc;
	for (int i = 0; i < H; i++)
		cin >> grid[i];
	char index = 'a';
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (grid[i][j] == '1') {
				Cluster c = find_cluster(grid, i, j);
				c.index = index;
				for (vector<Cluster>::iterator it = vc.begin(); it != vc.end(); it++) {
					if (it->same(c)) {
						c.index = it->index;
						break;
					}
				}
				if (c.index == index) {
					index++;
					vc.PB(c);
				}
				c.paint(grid);
			}
		}
	}
	for (int i = 0; i < H; i++) {
		cout << grid[i] << endl;
	}
	return 0;
}