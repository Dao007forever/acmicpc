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

#define MAXK 26
struct Node {
	Node *fail;
	Node *next[MAXK];
	int count;
	Node() {
		fail = NULL;
		count = 0;
		memset(next, 0, sizeof(next));
	}
};
struct AC_Automaton {
	Node *queue[500001];
	Node *root;

	AC_Automaton() {
		root = new Node();
	}

	void insert(char *str) {
		Node *p = root;
		for (int i = 0; str[i]; i++) {
			int index = str[i] - 'a';
			if (p->next[index] == NULL)
				p->next[index] = new Node();
			p = p->next[index];
		}
		p->count++;
	}

	void build() {
		int head = 0, tail = 0;
		root->fail = NULL;
		queue[head++] = root;
		while (head != tail) {
			Node *temp = queue[tail++];
			Node *p = NULL;
			for (int i = 0; i < MAXK; i++) {
				if (temp->next[i] != NULL) {
					if (temp == root) temp->next[i]->fail = root;
					else {
						p = temp->fail;
						while (p != NULL) {
							if (p->next[i] != NULL) {
								temp->next[i]->fail = p->next[i];
								break;
							}
							p = p->fail;
						}
						if (p == NULL) temp->next[i]->fail = root;
					}
					queue[head++] = temp->next[i];
				}
			}
		}
	}

	int match(char *str) {
		Node *p = root;
		int ret = 0;
		for (int i = 0, cnt = 0; str[i]; i++) {
			int index = str[i] - 'a';
			while (p->next[index] == NULL && p != root)
				p = p->fail;
			p = p->next[index];
			p = (p == NULL) ? root : p;
			Node *temp = p;
			while (temp != root && temp->count != -1) {
				ret += temp->count;
				temp->count = -1;
				temp = temp->fail;
			}
		}
		return ret;
	}
};
char keyWord[51];
char str[1000001];

int main() {
	freopen("in", "r", stdin);
	int Test, n;
	cin >> Test;
	while (Test--) {
		AC_Automaton AC;
		cin >> n;
		while (n--) {
			scanf("%s", keyWord);
			AC.insert(keyWord);
		}
		AC.build();
		scanf("%s", str);
		int ret = AC.match(str);
		cout << ret << endl;
	}
	return 0;
}
