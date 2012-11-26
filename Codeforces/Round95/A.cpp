#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

char str[150];
int main() {
	cin >> str;
	int len = strlen(str);
	int f1 = 1, f2 = 1;
	if (str[0] > 'Z') f1 = 0;
	for (int i = 1; i < len; i++) if (str[i] > 'Z')
		f2 = 0;
	if ((!f1 && f2) || (f1 && f2)) 
		for (int i = 0; i < len; i++)
			if (str[i] > 'Z') str[i] = str[i] - 'a' + 'A';
			else str[i] = str[i] - 'A' + 'a';
	cout << str << endl;
	return 0;
}
