#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

char s[2222];
int len, N[2222];

void init() {
	len = strlen(s);
	for (int i = 0; i < len; i++)
		N[len - i] = s[i] - '0';
}

bool odd() {
	if (N[1] & 1) return true;
	return false;
}

void Minus() {
	N[1]--;
	for (int i = 1; i <= len; i++)
		for (; N[i] < 0; ) {
			N[i + 1]--;
			N[i] += 10;
		}		   
}

void Div() {
	for (int i = len; i >= 1; i--) {
		if (N[i] % 2 == 0) N[i] /= 2;
		else {
			N[i] = (N[i] - 1) / 2;
			N[i - 1] += 10;
		}
	}
}

void output() {
	for (int i = len; i >= 1; i--)
		if (N[i]) {
			for (int j = i; j >= 1; j--)
				cout << N[j];
			cout << endl;
			return;
		}
}

int main() {
	freopen("in.txt", "r", stdin);
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		cin >> s;
		init();
		if (cas > 1) cout << endl;
		if (odd()) {
			Minus();
			Div();
			output();
		}
		else {
			Div();
			Minus();
			if (!odd()) Minus();
			output();
		}
	}
	return 0;
}
