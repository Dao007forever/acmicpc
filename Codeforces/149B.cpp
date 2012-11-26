#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int base;

int conv(char c) {
	if (c >= '0' && c <= '9') return c - '0';
	return c - 'A' + 10;
}

int solve(string s) {
	int ret = 0;
	for (int i = 0; i < s.size(); i++) {
		int t = conv(s[i]);
		if (t >= base) return 1 << 30;
		ret = ret * base + t;
		if (ret > 100) return 1 << 30;
	}
	return ret;
}

int main() {
	freopen("in.txt", "r", stdin);
	string s;
	cin >> s;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ':') s[i] = ' ';
	}
	stringstream ss(s);
	string a, b;
	ss >> a >> b;
	vector<int> v;
	for (base = 2; base <= 1000; base++) {
		if (solve(a) < 24 && solve(b) < 60)
			v.push_back(base);
	}
	if (v.size() > 100) {
		cout << -1;
		return 0;
	}
	if (v.size() == 0) {
		cout << 0;
		return 0;
	}
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	return 0;
}
