/*
 * 判断1是否能够组成一个立方体
 * 非常非常好的模拟题，跟Topcoder SRM417 div1 500pt一样
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

struct Move {
	int i, j;
	void (*move)();
	void (*back)();
};
Move move[4];
enum Face {TOP = 0, NORTH, WEST, EAST, SOUTH, BOTTON};
bool cube[6];
int paper[6][6];

void MoveNorth() {
	bool top = cube[TOP];
	cube[TOP] = cube[SOUTH];
	cube[SOUTH] = cube[BOTTON];
	cube[BOTTON] = cube[NORTH];
	cube[NORTH] = top;
}

void MoveEast() {
	bool top = cube[TOP];
	cube[TOP] = cube[WEST];
	cube[WEST] = cube[BOTTON];
	cube[BOTTON] = cube[EAST];
	cube[EAST] = top;
}

void MoveSouth() {
	bool top = cube[TOP];
	cube[TOP] = cube[NORTH];
	cube[NORTH] = cube[BOTTON];
	cube[BOTTON] = cube[SOUTH];
	cube[SOUTH] = top;
}

void MoveWest() {
	bool top = cube[TOP];
	cube[TOP] = cube[EAST];
	cube[EAST] = cube[BOTTON];
	cube[BOTTON] = cube[WEST];
	cube[WEST] = top;
}

void InitMoves() {
	move[0].i = -1;
	move[0].j = 0;
	move[0].move = MoveNorth;
	move[0].back = MoveSouth;

	move[1].i = 0;
	move[1].j = -1;
	move[1].move = MoveWest;
	move[1].back = MoveEast;

	move[2].i = 1;
	move[2].j = 0;
	move[2].move = MoveSouth;
	move[2].back = MoveNorth;

	move[3].i = 0;
	move[3].j = 1;
	move[3].move = MoveEast;
	move[3].back = MoveWest;
}

void SearchStart(int& i, int& j) {
	for (i = 0; i < 6; i++)
		for (j = 0; j < 6; j++)
			if (paper[i][j] == 1) return;
}

bool IsInside(int i, int j) {
	return (i >= 0 && i < 6) && (j >= 0 && j < 6);
}

void Flood(int i, int j) {
	cube[BOTTON] = true;
	paper[i][j] = 0;
	for (int k = 0; k < 4; k++) {
		int dest_i = i + move[k].i;
		int dest_j = j + move[k].j;
		if (!IsInside(dest_i, dest_j) || paper[dest_i][dest_j] == 0) continue;
		move[k].move();
		Flood(dest_i, dest_j);
		move[k].back();
	}
}

bool IsArmable() {
	memset(cube, 0, sizeof(cube));
	int i = 0, j = 0;
	SearchStart(i, j);
	Flood(i, j);
	for (int k = 0; k < 6; k++)
		if (!cube[k]) return false;
	return true;
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	int blank = 0;
	while (Test--) {
		if (blank) puts("");
		blank = 1;
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
				cin >> paper[i][j];
		InitMoves();
		if (IsArmable()) cout << "correct" << endl;
		else cout << "incorrect" << endl;
	}
	return 0;
}
