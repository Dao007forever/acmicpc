#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

char input[100050];
int arr[100050], c[100050];
int num[3], r1, r0, len;
bool res[4];

int toNum(char x) {
	if (x == '0') return 0;
	else if (x == '1') return 1;
	else return 2;
}

int main() {
	cin >> input;
	len = strlen(input);
	for (int i = 0; i < len; i++) 
		arr[i] = toNum(input[i]);
	for (int i = 0; i < len; i++) {
		num[arr[i]]++;
	}
	memset(res, false, sizeof(res));
	if (num[0] + num[2] > num[1])
		res[0] = true;
	if (num[0] + num[2] >= num[1] - 1 && num[1] + num[2] >= num[0]) {
		int x = len / 2, y = (len + 1) / 2;
		int sp = x - num[0];
		for (int i = 0, t = 0; i < len; i++) {
			if (arr[i] == 0)
				c[i] = 0;
			else if (arr[i] == 2 && t < sp) {
				c[i] = 0, t++;
			} else 
				c[i] = 1;
		}
		r0 = -1; r1 = -1;
		for (int i = 0; i < len; i++) {
			if (c[i] == 0) r0 = max(r0, i);
			else r1 = max(r1, i);
		}
		if (r0 < r1)
			res[1] = true;
		sp = y - num[1];
		for (int i = 0, t = 0; i < len; i++) {
			if (arr[i] == 1)
				c[i] = 1;
			else if (arr[i] == 2 && t < sp) {
				c[i] = 1; t++;
			} else
				c[i] = 0;
		}
		r0 = -1; r1 = -1;
		for (int i = 0; i < len; i++) {
			if (c[i] == 0) r0 = max(r0, i);
			else r1 = max(r1, i);
		}
		if (r1 < r0)
			res[2] = true;
/*		if (num[0] == num[1] + num[2] || num[0] == num[1] + num[2] - 1) {
			if (l0 > max(r1, rr1))
				res[1] = true;
		} else if (num[1] == num[0] + num[2] || num[1] == num[0] + num[2] + 1) {
			if (r1 < min(l0, ll0))
				res[2] = true;
		} else {
			if (min(l0, ll0) < r1)
				res[1] = true;
			if (max(r1, rr1) < l0)
				res[2] = true;
		}*/
	}
	if (num[1] + num[2] > num[0] + 1)
		res[3] = true;
	if (res[0]) cout << "00" << endl;
	if (res[1]) cout << "01" << endl;
	if (res[2]) cout << "10" << endl;
	if (res[3]) cout << "11" << endl;
	return 0;
}
