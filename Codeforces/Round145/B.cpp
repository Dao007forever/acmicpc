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

int n, k;
int main(int argc, char const *argv[])
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> n >> k;
	std::vector<pair<int, int> > a;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a.PB(MP(x, i + 1));
	}
	sort(a.begin(), a.end());
	reverse(a.begin(), a.end());
	cout << a[k - 1].first << endl;
	for (int i = 0; i < k; i++)
		printf("%d%c", a[i].second, i == k - 1 ? '\n' : ' ');
	return 0;
}