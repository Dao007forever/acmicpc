//path is the final hamiltion path
void dirac(bool g[maxn][maxn], int n, int *path) {
	static int nxt[maxn];
	static bool vis[maxn];
	memset(nxt, 255, sizeof(nxt));
	memset(vis, 0, sizeof(vis));

	int S = 0, T;
	for (T = 1; !g[S][T]; T++);

	nxt[S] = T;
	nxt[T] = S;
	vis[S] = vis[T] = 1;

	for (int num = 2; num != n; ) {
//Step 1:
		while (1) {
			bool ok = true;
			for (int i = 0; i < n; i++) {
				if (vis[i]) continue;
				if (g[i][S]) {
					vis[i] = 1, nxt[i] = S, S = i, ok = false, num++;
				} else if (g[T][i]) {
					vis[i] = 1, nxt[T] = i, T = i, ok = false, num++;
				}
			}
			if (ok) break;
		}
		nxt[T] = S; //fix the circuit!
//Step 2,3:
		if (!g[S][T]) {
			int tgt = -1;
			int prev = S, next;
			for (int i = nxt[S]; nxt[i] != T; i = next) {
				next = nxt[i];
				nxt[i] = prev;
				prev = i;
				if (g[S][next] && g[T][i]) {
					tgt = i;
					break;
				}
			}
			//assume tgt != -1
			nxt[S] = next;
			nxt[T] = tgt;
			S = tgt;
		}
		//now S->T is a circuit
//Step 4:
		if (num == n) break;
		for (int i = 0; i < n; i++) {
			if (vis[i]) continue;
			int j = S;
			do {
				if (g[i][j]) {
					T = j;
					S = nxt[j];
					goto out;
				}
			} while ((j=nxt[j]) != S);
		}
		out:;
	}
	int len = 0, i = S;
	do {
		path[len++] = i;
	} while ((i=nxt[i]) != S);
	//assume len = n;
}

