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

#define MAXK 27
struct Node {
	Node *fail;
	Node *next[MAXK];
	int id;//The identity of the word in the input
	int count;//The occurences of the word
	Node() {
		id = 0;
		fail = NULL;
		count = 0;
		memset(next, 0, sizeof(next));
	}
};
int cnt[1111];
char keyWord[1111][55];
char str[2000005];
struct AC_Automaton {
	Node *queue[50001];
	Node *root;

	void init() {
		root = new Node();
	}

	//insert a word
	void insert(char *str, int index) {
		Node *p = root;
		for (int i = 0; str[i]; i++) {
			int index = str[i] - 'A';
			if (p->next[index] == NULL)
				p->next[index] = new Node();
			p = p->next[index];
		}
		p->count++;
		p->id = index;
	}

	//Build fail pointer
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

	void match(char *str) {
		Node *p = root;
		for (int i = 0; str[i]; i++) {
			int index = str[i] - 'A';
			//If match fails
			if (index < 0 || index >= 26) {
				p = root;
				continue;
			}
			while (p->next[index] == NULL && p != root)
				p = p->fail;
			p = p->next[index];
			p = (p == NULL) ? root : p;
			Node *temp = p;
			while (temp != root) {
				cnt[temp->id]++;
				temp = temp->fail;
			}
		}
	}
};

AC_Automaton AC;
int main() {
	freopen("3065.in", "r", stdin);
	int n;
	while (cin >> n) {
		AC.init();
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= n; i++) {
			scanf("%s", keyWord[i]);
			AC.insert(keyWord[i], i);
		}
		AC.build();
		scanf("%s", str);
		AC.match(str);
		for (int i = 1; i <= n; i++)
			if (cnt[i]) {
				printf("%s: %d\n", keyWord[i], cnt[i]);
			}
	}
	return 0;
}
