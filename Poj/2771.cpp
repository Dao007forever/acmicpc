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

#define MAXN 505
struct Person {
	int height;
	string music, sport;
	Person() {}
	Person(int height, string music, string sport) {
		this->height = height;
		this->music = music;
		this->sport = sport;
	}
};
int adj[505][505];
int mk[505], mate[505];
int nx, ny;

int dfs(int u) {
	for (int v = 0; v < ny; v++) {
		if (adj[u][v] && !mk[v]) {
			mk[v] = true;
			if (mate[v] == -1 || dfs(mate[v])) {
				mate[v] = u;
				return 1;
			}
		}
	}
	return 0;
}

int maxMatch() {
	memset(mate, -1, sizeof(mate));
	int ret = 0;
	for (int i = 0; i < nx; i++) {
		memset(mk, 0, sizeof(mk));
		ret += dfs(i);
	}
	return ret;
}

bool check(const Person &a, const Person &b) {
	if (abs(a.height - b.height) > 40) return false;
	if (a.music != b.music) return false;
	if (a.sport == b.sport) return false;
	return true;
}

int main(int argc, char const *argv[])
{
	int Test, n;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		vector<Person> m, f;
		for (int i = 0; i < n; i++) {
			int h;
			string s1, s2, s3;
			cin >> h >> s1 >> s2 >> s3;
			if (s1[0] == 'M') m.PB(Person(h, s2, s3));
			else f.PB(Person(h, s2, s3));
		}
		memset(adj, 0, sizeof(adj));
		nx = SZ(m), ny = SZ(f);
		for (int i = 0; i < nx; i++)
			for (int j = 0; j < ny; j++) {
				if (check(m[i], f[j])) {
					// cout << i << " " << j << endl;
					adj[i][j] = 1;
				}
			}
		int ret = maxMatch();
		printf("%d\n", nx + ny - ret);
	}
	return 0;
}