/*
 *  Edmonds Blossom-Contraction Algorithm
 */
#define maxn 800
#define maxm maxn * maxn

struct Nod {
	int b, nxt;
	void init(int b, int nxt) {
		this->b = b;
		this->nxt = nxt;
	}
};

struct Graph {
    int E[maxn], n;                //图
    Nod buf[maxm];    int len;    //资源
    
    int match[maxn];
    
    void init(int n) {
        if(n>maxn) {
            int a = 1, b = 0;
            int c = a / b;
        }
        this->n = n;
        memset(E, 255, sizeof(E));
        len = 0;
    }
    void addEdge(const int &a, const int &b) {
        buf[len].init(b, E[a]);        E[a] = len ++;
        buf[len].init(a, E[b]);        E[b] = len ++;
    }
    int solve() {    //返回最大匹配数，匹配的人数为这个数的2倍
        memset(match, -1, sizeof(match));
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (match[i] == -1) {
                ans += bfs(i);
            }
        }
        return ans;
    }
private:
    int Q[maxn], pre[maxn], base[maxn];
    bool hash[maxn];
    bool in_blossom[maxn];
    int bfs(int p) {
        memset(pre, -1, sizeof(pre));
        memset(hash, 0, sizeof(hash));
        for (int i = 0; i < n; ++i) {
            base[i] = i;
        }
        Q[0] = p;
        hash[p] = 1;
        for (int s = 0, t = 1; s < t; ++s) {
            int u = Q[s], v;
            for(int iter = E[u]; iter != -1; iter = buf[iter].nxt) {
                v = buf[iter].b;
                if (base[u] != base[v] && v != match[u]) {
                    if (v == p || (match[v] != -1 && pre[match[v]] != -1)) {
                        int b = contract(u, v);
                        for (int i = 0; i < n; ++i) {
                            if (in_blossom[base[i]]) {
                                base[i] = b;
                                if (hash[i] == 0) {
                                    hash[i] = 1;
                                    Q[t++] = i;
                                }
                            }
                        }
                    } else if (pre[v] == -1) {
                        pre[v] = u;
                        if (match[v] == -1) {
                            argument(v);
                            return 1;
                        } else {
                            Q[t++] = match[v];
                            hash[match[v]] = 1;
                        }
                    }
                }
            }
        }
        return 0;
    }
    void argument(int u) {
        while (u != -1) {
            int v = pre[u];
            int k = match[v];
            match[u] = v;
            match[v] = u;
            u = k;
        }
    }
    void change_blossom(int b, int u) {
        while (base[u] != b) {
            int v = match[u];
            in_blossom[base[v]] = in_blossom[base[u]] = true;
            u = pre[v];
            if (base[u] != b) {
                pre[u] = v;
            }
        }
    }
    int contract(int u, int v) {
        memset(in_blossom, 0, sizeof(in_blossom));
        int b = find_base(base[u], base[v]);
        change_blossom(b, u);
        change_blossom(b, v);
        if (base[u] != b) {
            pre[u] = v;
        }
        if (base[v] != b) {
            pre[v] = u;
        }
        return b;
    }
    int find_base(int u, int v) {
        static bool in_path[maxn];
        memset(in_path, 0, sizeof(in_path));
        while (true) {
            in_path[u] = true;
            if (match[u] == -1) {
                break;
            }
            u = base[pre[match[u]]];
        }
        while (!in_path[v]) {
            v = base[pre[match[v]]];
        }
        return v;
    }
} g;
