#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
using namespace std;

struct SegTree {
#define SIZE 200010
#define MEM 2*SIZE+10 
	long long L[MEM], R[MEM], n;
	long long validNum[MEM];
	long long sum[5][MEM];
	
	void init(long long size) {
		for(n = 1; n < size; n <<= 1);
		long long i;
		for(i = n; i < 2*n; i ++) {
			L[i] = i-n;
			R[i] = i+1-n;
		}
		for(i = n-1; i >= 1; i --) {
			L[i] = L[2*i];
			R[i] = R[2*i+1];
		}
		memset(validNum, 0, sizeof(validNum));
		memset(sum, 0, sizeof(sum));
	}
	void insert(long long l, long long r, long long v, long long i=1) {
		if(l <= L[i] && r >= R[i]) {
			validNum[i] = 1;
			sum[0][i] = v;
			sum[1][i] = 0;
			sum[2][i] = 0;
			sum[3][i] = 0;
			sum[4][i] = 0;
		} else {
			if(l < (L[i]+R[i])/2)	insert(l, r, v, 2*i);
			if(r > (L[i]+R[i])/2)	insert(l, r, v, 2*i+1);
			update(i);
		}
	}
	void remove(long long l, long long r, long long i=1) {
		if(l <= L[i] && r >= R[i]) {
			validNum[i] = 0;
			sum[0][i] = 0;
			sum[1][i] = 0;
			sum[2][i] = 0;
			sum[3][i] = 0;
			sum[4][i] = 0;
		} else {
			if(l < (L[i]+R[i])/2)	remove(l, r, 2*i);
			if(r > (L[i]+R[i])/2)	remove(l, r, 2*i+1);
			update(i);
		}
	}
	void update(long long i) {
		validNum[i] = validNum[2*i] + validNum[2*i+1];
		long long t = validNum[2*i]%5;
		for(long long j = 0; j < 5; j ++) {
			sum[j][i] = sum[j][2*i] + sum[ (5-t+j)%5 ][2*i+1];
		}
	}
} seg;

char c[100010];
int v[100010];

int main() {
	int n;
	char str[10];
	while(scanf("%d", &n) != EOF) {
		map<int,int>maps;
		for(int i = 1; i <= n; i ++) {
			scanf("%s", str);
			c[i] = str[0];
			if(c[i]=='a' || c[i]=='d') {
				scanf("%d", v+i);
				maps[v[i]];
			}
		}
		int count = 0;
		for(map<int,int>::iterator iter = maps.begin(); iter != maps.end(); iter ++) {
			iter->second = ++ count;
		}
		///////
		seg.init(n);
		for(long long i = 1; i <= n; i ++) {
			if(c[i]=='a') {
				int idx = maps[v[i]];
				seg.insert(idx-1,idx, v[i]);
			} else if(c[i]=='d') {
				int idx = maps[v[i]];
				seg.remove(idx-1,idx);
			} else {
				cout << seg.sum[2][1] << endl;
			}
		}
	}
	return 0;
}
