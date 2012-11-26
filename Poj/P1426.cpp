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

const int size = 10000005;
long long q[size];
int main(int argc, char const *argv[])
{
	freopen("in.txt", "r", stdin);
	int n;
	while (scanf("%d", &n) && n) {
		int head = 0, tail = 0;
		q[tail++] = 1;
		while (head <= tail) {
			long long x = q[head]; head = (head + 1) % size;
			if (x % n == 0) {
				cout << x << endl;
				break;
			}

			x *= 10;
			if (x % n == 0) {
				cout << x << endl;
				break;
			}
			q[tail] = x; tail = (tail + 1) % size;

			x++;
			if (x % n == 0) {
				cout << x << endl;
				break;
			}
			q[tail] = x; tail = (tail + 1) % size;
		}
	}
	return 0;
}