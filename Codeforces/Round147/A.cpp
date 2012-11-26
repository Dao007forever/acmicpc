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

int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	vector<pair<int, int> > p(n);
	for (int i = 0; i < n; i++) {
		cin >> p[i].first >> p[i].second;
	}
	sort(p.begin(), p.end());
	int ret = 1;
	for (int i = 0; i < n;) {
		int j;
		for (j = i + 1; j < n && p[i] == p[j]; j++);
		ret = max(ret, j - i);
		i = j;
	}
	cout << ret << endl;
	return 0;
}