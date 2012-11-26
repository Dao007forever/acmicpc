/*
 * 统计的好题，设f(n)为所有[1,n]的数中出现1的个数总和，已知n，f(x)=n，求x
 * 二分x，f(x)的求法为：依次统计每一位上出现1的个数（个位为第0为），若统计第i位上出现1的个数，分为两部分统计，前半部分和后半部分，前半部分的个数是(x/10^(i+1)*10^i)，后半部分的个数是g(x mod 10^(i+1), i)，函数g(x,i)的方程为：若x<10^i（即首位为0），则g(x,i)=0；若10^i<=x<2*10^i（即首位为1），则g(x,i)=x-10^i+1；若x>=2*10^i（即首位大于1），则g(x,i)=10^i
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

long long power[20];

long long G(long long n, int i) {
	if (n < power[i]) return 0;
	if (n >= power[i] * 2) return power[i];
	else return n - power[i] + 1;
}

long long count(long long x) {
	long long ret = 0;
	for (int i = 0; i < 18; i++) {
		long long a = x / power[i + 1];
		if (power[i] > x) break;
		long long b = x % power[i + 1];
		ret += a * power[i];
		ret += G(b, i);
	}
	return ret;
}

int main() {
	power[0] = 1;
	for (int i = 1; i <= 18; i++)
		power[i] = power[i - 1] * 10;
	long long x;
	cin >> x;
	if (x == 1) {
		cout << 1 << endl;
		return 0;
	}
	count(11);
	long long l = 1, r = 1000000000000000000LL, ret;
	while (r - l > 1) {
		long long mid = (l + r) >> 1;
		if (count(mid) >= x) {
			ret = mid;
			r = mid;
		} else l = mid;
	}
	if (count(ret) == x) cout << ret << endl;
	else cout << "Petr lies" << endl;
	return 0;
}
