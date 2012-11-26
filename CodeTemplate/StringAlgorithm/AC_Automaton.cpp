/*
 * AC_Automaton with pointers
 */
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

/*
 * AC_Automaton with arrays, convenient for DP.
 */
struct AC_Automaton {

	int size;
	int tag[MAXN];
	int fail[MAXN];
	int trie[MAXN][MAXK];

	void init() {
		tag[0] = 0;
		fill(trie[0], trie[0] + 4, -1);
		size = 1;
	}

	void insert(char *str, int t) {
		int p = 0;
		for (int i = 0; str[i]; i++) {
			int index = ID(str[i]);
			if (trie[p][index] == -1) {
				tag[size] = 0;
				fill(trie[size], trie[size] + MAXK, -1);
				trie[p][index] = size++;
			}
			p = trie[p][index];
		}
		tag[p] |= t;
	}

	void build() {
		queue<int> Q;
		fail[0] = 0;
		for (int i = 0; i < MAXK; i++) {
			if (trie[0][i] != -1) {
				fail[trie[0][i]] = 0;
				Q.push(trie[0][i]);
			} else {
				trie[0][i] = 0;
			}
		}
		while (!Q.empty()) {
			int p = Q.front();
			Q.pop();
			tag[p] |= tag[fail[p]];
			for (int i = 0; i < MAXK; i++) {
				if (trie[p][i] != -1) {
					fail[trie[p][i]] = trie[fail[p]][i];
					Q.push(trie[p][i]);
				} else {
					trie[p][i] = trie[fail[p]][i];
				}
			}
		}
	}
}AC;
