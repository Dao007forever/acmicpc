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
char keyWord[1111];
char str[5100005], p[5100005], x[5100005];
struct AC_Automaton {
	Node *queue[5000001];
	Node *root;

	void init() {
		root = new Node();
	}

	//insert a word
	void insert(char *str) {
		Node *p = root;
		for (int i = 0; str[i]; i++) {
			int index = str[i] - 'A';
			if (p->next[index] == NULL)
				p->next[index] = new Node();
			p = p->next[index];
		}
		p->count++;
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

	int match(char *str) {
		Node *p = root;
		int ret = 0;
		for (int i = 0; str[i]; i++) {
			int index = str[i] - 'A';
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
}AC;

void change() {
	int len, c;
	len = strlen(str);  
    c = 0;
    for (int i = 0; i < len; i++) {  
		if (str[i] != '[') {  
			p[c++] = str[i];  
        } else {  
			i++;
            int q = 0;  
            while (str[i] >= '0' && str[i] <= '9') {  
                q *= 10;  
                q += str[i] - '0';  
                i++;  
            }
            int k = 0;  
            while (str[i] != ']') {  
                x[k++] = str[i];  
                i++;
            }
            for (int j = 0; j < q; j++) {  
                for (int jj = 0; jj < k; jj++) {  
                    p[c++] = x[jj];  
                }
            }
        }
	}
    p[c] = 0;
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		int n;
		AC.init();
		cin >> n;
		for (int i = 0; i < n; i++) {
			scanf("%s", keyWord);
			AC.insert(keyWord);
		}
		AC.build();
		scanf("%s", str);
		change();
		int ret = AC.match(p);
		reverse(p, p + strlen(p));
		ret += AC.match(p);
		printf("%d\n", ret);
	}
	return 0;
}

