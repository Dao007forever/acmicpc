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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;
typedef vector<vector<int> > VII;

#define maxn 26
struct BipartiteGraph {

    int nx, ny;
    int delX, delY;
    bool used[maxn], g[maxn][maxn];
    bool X[maxn], Y[maxn];
    int mx[maxn], my[maxn];

    void init(int nx, int ny) {
        this->nx = nx; this->ny = ny;
        memset(g, 0, sizeof(g));
    }

    void addEdge(int u, int v) {
        g[u][v] = true;
        //cout << u << " " << v << endl;
    }

    bool find(int u) {
        for (int v = 0; v < ny; v++) {
            if (!used[v] && g[u][v]) {
                used[v] = true;
                if (my[v] == -1 || find(my[v])) {
                    mx[u] = v;
                    my[v] = u;
                    return 1;
                }
            }
        }
        return 0;
    }

    int MaxMatch() {
        for (int i = 0; i < nx; i++)
            mx[i] = -1;
        for (int j = 0; j < ny; j++)
            my[j] = -1;
        int ret = 0;
        for (int i = 0; i < nx; i++) {
            memset(used, false, sizeof(used));
            if (find(i)) ret++;
        }
        return ret;
    }

    bool findY(int u) {
        for (int v = 0; v < ny; v++) {
            if (v != delY && !used[v] && g[u][v]) {//notice it's g[u][v]
                used[v] = 1;
                if (my[v] == -1 || findY(my[v]))
                    return 1;
            }
        }
        return 0;
    }

    bool findX(int u) {
        for (int v = 0; v < nx; v++) {
            if (v != delX && !used[v] && g[v][u]) {//notice it's g[v][u]
                used[v] = 1;
                if (mx[v] == -1 || findX(mx[v]))
                    return 1;
            }
        }
        return 0;
    }

    //X[i]=1 or Y[i]=1 means it's not a key vertex!!!
    void solve() {
        memset(X, 0, sizeof(X));
        memset(Y, 0, sizeof(Y));
        for (int i = 0; i < nx; i++) {
            if (mx[i] == -1) {
                X[i] = 1;
            } else {
                delY = mx[i];
                memset(used, 0, sizeof(used));
                if (findY(i)) Y[delY] = 1;
            }
        }
        for (int j = 0; j < ny; j++) {
            if (my[j] == -1) {
                Y[j] = 1;
            } else {
                delX = my[j];
                memset(used, 0, sizeof(used));
                if (findX(j)) X[delX] = 1;
            }
        }
    }

}g;
string buf;
bool mk[maxn + 1];
int mate[maxn + 1];
VII vt;
int del;

bool match(VII vec, vector<int> &ret) {
	vt = vec;
	ret = vector<int>(maxn);
	if (vec.size() > 26) return false;
	g.init(vt.size(), maxn);
	for (int i = 0; i < vt.size(); i++) {
		for (int j = 0; j < vt[i].size(); j++) {
			if (vt[i][j] == 1) {
				g.addEdge(i, j);
				//cout << i << " " << j << endl;
			}
		}
	}
	int cnt = g.MaxMatch();
	if (cnt != vt.size()) return false;
	g.solve();
	for (int i = 0; i < maxn; i++)
		if (g.Y[i]) ret[i] = 1;
	return true;
}

vector<int> getSub() {
	vector<int> vec(maxn);
	for (int i = 0; i < buf.size(); i++)
		if (buf[i] >= 'A' && buf[i] <= 'Z') {
			vec[buf[i] - 'A'] = 1;
		}
	return vec;
}

void change(vector<int> &vec, vector<int> vec2) {
	for (int i = 0; i < maxn; i++)
		vec[i] = vec[i] & vec2[i];
}

bool solve() {
	vector<VII> vec;
	vector<int> possible;
	while (true) {
		getline(cin, buf);
		if (buf == "<") {
			vec.PB(VII());
		} else if (buf == ">") {
			if (!match(vec.back(), possible)) return false;
			vec.pop_back();
			if (vec.size() == 0) return true;
			change(vec.back().back(), possible);
		} else {
			vec.back().PB(getSub());
		}
	}
	return true;
}

int main(int argc, char const *argv[])
{
	int ret = solve();
	if (ret) puts("Got It!");
	else puts("No Solution");
	return 0;
}