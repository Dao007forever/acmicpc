#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int n;
int a[111111];

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	sort(a, a + n);
	int ret = 0;
	for (int i = n - 1, j = 0; i >= j; i--) {
		int sum = a[i];
		while (sum + a[j] <= 4 && i > j) {
			sum += a[j];
			j++;
		}
		ret++;
	}
	cout << ret << endl;
}
