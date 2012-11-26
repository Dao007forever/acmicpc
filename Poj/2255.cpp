/*
 * 2255.cpp
 *
 *  Created on: 2011-1-13
 *      Author: zhangyang
 */

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

int N , len;
char p[28] , m[28] , h[28];

int Find(char str[] , int s , int t , char c)
{
	for (int i = s ; i <= t ; i++)
	{
		if (str[i] == c)
			return i;
	}
	return -1;
}

void FindPost(int ps , int pt , int ms , int mt)
{
	if (ps > pt || ms > mt)
		return;
	if (ps == pt)
	{
		len--;
		h[len] = p[ps];
		return;
	}
	else
	{
		int mid = Find(m , ms , mt , p[ps]);
		len--;
		h[len] = p[ps];
		FindPost(pt - mt + mid + 1 , pt , mid +  1 , mt);
		FindPost(ps + 1 , ps + mid - ms , ms , mid - 1);
	}
}

int main()
{
//	freopen("a" , "r" , stdin);
	while (cin >> p >> m)
	{
			N = strlen(p);
			len = N;
			h[N] = '\0';
			FindPost(0 , N - 1 , 0 , N - 1);
			cout << h << endl;
	}
	return 0;
}
