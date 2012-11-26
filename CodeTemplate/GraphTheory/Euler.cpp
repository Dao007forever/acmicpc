//vector<string> ans record the euler path
void dfs(int u, int id) {
	for (int i = Head[u]; i != -1; i = edge[i].next)
		if (!edge[i].vis) {
			edge[i].vis = 1;
			dfs(edge[i].v, i);
		}
	if (id != -1) ans.PB(name[id]);
}

//return -1 if there are no euler path, or return the start of the euler path
int check() {
	int num = 0, t1 = 0, t2 = 0, id = -1;
	for (int i = 0; i < 26; i++) {
		if (vis[i]) {
			if (find(i) == i)
				num++;
			if (indeg[i] != outdeg[i]) {
				if (indeg[i] - outdeg[i] == 1)
					t1++;
				else if (outdeg[i] - indeg[i] == 1) {
					t2++;
					id = i;
				} else return -1;
			}
		}
	}
	if (num != 1) return -1;
	if (!((t1 == 1 && t2 == 1) || (t1 == 0 && t2 == 0)))
		return -1;
	if (id == -1) {
		for (int i = 0; i < 26; i++)
			if (outdeg[i] > 0) {
				id = i;
				break;
			}
	}
	return id;
}

bool cmp(string a, string b) {
	return a >= b;//notice it is ">=" !
}
sort(s, s + n, cmp);//If we want the lexicographically least path