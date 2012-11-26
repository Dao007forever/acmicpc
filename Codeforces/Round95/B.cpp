#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

long long num[25];
int offset = 11, n;

int main() {
	cin >> n;
	memset(num, 0 , sizeof(num));
	for (int i = 0, t; i < n; i++) {
		cin >> t;
		num[offset + t]++;
	}
	long long res = 0;
	for (int i = 1; i <= 10; i++)
		res += num[offset - i] * num[offset + i];
	res += num[offset] * (num[offset] - 1) / 2;
	cout << res << endl;
}
