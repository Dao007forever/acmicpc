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

int n, m;
int a[55];

int main(int argc, char const *argv[])
{
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	sort(a, a + n);
	reverse(a, a + n);
	for (int i = 0; i < n && m; i++) {
		for (int j = i; j < n && m; j++) {
			m--;
			cout << i + 1;
			for (int k = 0; k < i; k++)
				cout << " " << a[k];
			cout << " " << a[j] << endl;
		}
	}
	return 0;
}