/*
 * Author : Yang Zhang
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

struct Arithmetic {
	long long x, y, z;
}A[100000];
int n;
char buffer[10000];

int calc(long long bound) {
	LL sum = 0;
	for (int i = 0; i < n; i++) {
		LL tmp = min(bound, A[i].y);
		if (tmp < A[i].x) continue;
		sum = (sum + (tmp - A[i].x) / A[i].z + 1) % 2;
	}
	return sum;
}

int count(LL t) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if (t < A[i].x || t > A[i].y) continue;
		if ((t - A[i].x) % A[i].z == 0) sum++;
  	}
	return sum;
}

void read() {
	A[n].x = A[n].y = A[n].z = 0;
	int i = 0;
	for (; buffer[i] > '9' || buffer[i] < '0'; i++);
	for (; buffer[i] >= '0' && buffer[i] <= '9'; i++)
		
}

int main() {
	freopen("in.txt", "r", stdin);
	do gets(buffer); while (buffer[0] > '9' || buffer[0] < '0');
	while (true) {
		/*		while (!buffer[0]) gets(buffer);
		n = 1;
		sscanf(buffer, "%lld%lld%lld", &A[0].x, &A[0].y, &A[0].z);
		while (gets(buffer) && buffer[0] >= '0' && buffer[0] <= '9') {
			sscanf(buffer, "%lld%lld%lld", &A[n].x, &A[n].y, &A[n].z);
			++n;
			}*/
		n = 0;
		bool flag = 1;
		do {
			read();
			flag &= (gets(buffer) != NULL);
		}while (flag && buffer[0] >= '0' && buffer[0] <= '9');

		LL l = 1, r = 10000000000LL;
		if (calc(r) % 2 == 0) {
			printf("no corruption\n");
			continue;
		}

		while (l <= r) {
			long long mid = (l + r) / 2;
			if (calc(mid) % 2) r = mid - 1;
			else l = mid + 1;
		}
		printf("%lld %d\n", r + 1, count(r + 1));

		if (!flag) return 0;
		do
			if (gets(buffer) == NULL) return 0;
		while (buffer[0] > '9' || buffer[0] < '0');
	}
	return 0;
}
