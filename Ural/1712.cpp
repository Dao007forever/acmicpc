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

char a[7][7],b[7][7],t[7][7];
inline void Rota() {
    for (int i = 1;i <= 4; i++)
        for (int j = 1;j <= 4; j++)
            t[i][j] = a[5 - j][i];
    memcpy(a, t, sizeof(t));
}
int main() {
    for (int i = 1;i <= 4; i++)
        scanf("%s", a[i] + 1);
    for (int i = 1;i <= 4; i++)
        scanf("%s", b[i] + 1);
	string ans;
    for (int i = 1;i <= 4; i++)
    {
        for (int j = 1;j <= 4; j++)
            for (int k = 1;k <= 4; k++)
                if (a[j][k] == 'X')
					ans += b[j][k];
        Rota();
    }
	cout << ans << endl;
    return 0;
}
