#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Person {
	string name;
	int a, h;
}p[3333];
int n;

bool cmp(Person A, Person B) {
	return A.a < B.a;
}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> p[i].name >> p[i].a;
	}
	sort(p + 1, p + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		if (p[i].a >= i) {
			cout << -1;
			return 0;
		}
		p[i].h = i - p[i].a;
		for (int j = 1; j < i; j++)
			if (p[j].h >= p[i].h) p[j].h++;
	}
	for (int i = 1; i <= n; i++)
		cout << p[i].name << " " << p[i].h << endl;
	return 0;
}
