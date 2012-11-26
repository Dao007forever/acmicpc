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

#define MAXK 128
struct Node {
	Node *fail;
	Node *next[MAXK];
	int id;
	int count;
	Node() {
		id = 0;
		count = 0;
		fail = NULL;
		memset(next, 0, sizeof(next));
	}
};
vector<int> ans;
struct AC_Automaton {
	Node *queue[500001];
	Node *root;

	void init() {
		root = new Node();
	}

	//insert a word
	void insert(char *str, int index) {
		Node *p = root;
		for (int i = 0; str[i]; i++) {
			int index = str[i];
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
			int index = str[i];
			while (p->next[index] == NULL && p != root)
				p = p->fail;
			p = p->next[index];
			p = (p == NULL) ? root : p;
			Node *temp = p;
			while (temp != root) {
				if (temp->id > 0)
					ans.push_back(temp->id);
				temp = temp->fail;
			}
		}
	}
}AC;

char keyWord[222];
char str[11111];
int main() {
	freopen("in", "r", stdin);
	int n, m;
	while (scanf("%d", &n) != EOF) {
		AC.init();
		for (int i = 1; i <= n; i++) {
			scanf("%s", keyWord);
			AC.insert(keyWord, i);
		}
		AC.build();
		scanf("%d", &m);
		int ret = 0;
		for (int i = 1; i <= m; i++) {
			scanf("%s", str);
			ans.clear();
			AC.match(str);
			if (ans.size() > 0) {
				ret++;
				printf("web %d: ", i);
				sort(ans.begin(), ans.end());
				for (int i = 0; i < ans.size() - 1; i++)
					printf("%d ", ans[i]);
				printf("%d\n", ans[ans.size() - 1]);
			}
		}
		printf("total: %d\n", ret);
	}
	return 0;
}
