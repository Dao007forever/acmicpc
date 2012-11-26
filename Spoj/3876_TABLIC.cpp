/*
 * 有一个n*n的棋盘，有k条命令, 每条命令是将某个数字移动到指定位置, n<=10000,k<=1000
 * 因为k很小，所以只需要实时记录这k个数的位置即可，然后O(k^2)模拟
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

const int maxn = 1111;
struct node {
	int num, x, y;
}cmd[maxn];
vector<node> res;
int N, M;

int main()
{
	freopen("in", "r", stdin);
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> cmd[i].num >> cmd[i].x >> cmd[i].y;
		cmd[i].x--; cmd[i].y--;
		bool flag = true;
		for (int j = 0; j < i; j++)
			flag &= cmd[i].num != cmd[j].num;
		if (flag) {
			node tmp;
			tmp.num = cmd[i].num;
			tmp.x = (cmd[i].num - 1) / N;
			tmp.y = (cmd[i].num - 1) % N;
			res.push_back(tmp);
		}
	}

	for (int i = 0; i < M; i++) {
		int x, y, dx, dy;
		for (int j = 0; j < res.size(); j++) 
			if (cmd[i].num == res[j].num) {
				x = res[j].x;
				dy = cmd[i].y - res[j].y;
				if (dy < 0) dy += N;
			}
		for (int j = 0; j < res.size(); j++) {
			if (res[j].x == x) res[j].y += dy;
			if (res[j].y >= N) res[j].y -= N;
		}
		for (int j = 0; j < res.size(); j++) 
			if (cmd[i].num == res[j].num) {
				y = res[j].y;
				dx = cmd[i].x - res[j].x;
				if (dx < 0) dx += N;
			}
		for (int j = 0; j < res.size(); j++) {
			if (res[j].y == y) res[j].x += dx;
			if (res[j].x >= N) res[j].x -= N;
		}

		cout << dx + dy << endl;
	}
	return 0;
}
