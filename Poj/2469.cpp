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

int data[111][66];
int res[55], temp[55];

int main()
{
	freopen("a", "r", stdin);
		int k;
		cin >> k;
		for (int i = 1; i <= k; i++)
			for (int j = 1; j <= 52; j++)
				cin >> data[i][j];
		getchar();
		string input;

		for (int i = 1; i <= 52; i++)
			res[i] = i;
		int blank = false;
		while (getline(cin, input))
		{
			if (blank) puts("");
			blank = true;
			if (input == "") break;
			int t = atoi(input.c_str());
			for (int i = 1; i <= 52; i++)
				temp[i] = res[data[t][i]];
			memcpy(res, temp, sizeof(res));
			input = "";
			for (int i = 1; i <= 52; i++)
			{
				int row, col;
				row = (res[i] - 1) / 13;
				col = (res[i] - 1) % 13;
				if (col >= 0 && col <= 8) cout << col + 2;
				else
				{
					switch (col)
					{
						case 9:
							cout << "Jack";
							break;
						case 10:
							cout << "Queen";
							break;
						case 11:
							cout << "King";
							break;
						case 12:
							cout << "Ace";
							break;
					}
				}
				cout << " of ";
				switch (row)
				{
					case 0:
						cout << "Clubs" << endl;
						break;
					case 1:
						cout << "Diamonds" << endl;
						break;
					case 2:
						cout << "Hearts" << endl;
						break;
					case 3:
						cout << "Spades" << endl;
						break;
				}
			}
		}
	return 0;
}

