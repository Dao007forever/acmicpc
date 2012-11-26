#define MAXN 405
struct BipartiteGraph {

    int nx, ny;
    int delX, delY;
    bool used[MAXN], g[MAXN][MAXN];
    bool X[MAXN], Y[MAXN];
    int mx[MAXN], my[MAXN];

    void init(int nx, int ny) {
        this->nx = nx; this->ny = ny;
        memset(g, 0, sizeof(g));
    }

    void addEdge(int u, int v) {
        g[u][v] = true;
        //cout << u << " " << v << endl;
    }

    bool find(int u) {
        for (int v = 0; v < ny; v++) {
            if (!used[v] && g[u][v]) {
                used[v] = true;
                if (my[v] == -1 || find(my[v])) {
                    mx[u] = v;
                    my[v] = u;
                    return 1;
                }
            }
        }
        return 0;
    }

    int MaxMatch() {
        for (int i = 0; i < nx; i++)
            mx[i] = -1;
        for (int j = 0; j < ny; j++)
            my[j] = -1;
        int ret = 0;
        for (int i = 0; i < nx; i++) {
            memset(used, false, sizeof(used));
            if (find(i)) ret++;
        }
        return ret;
    }

    bool findY(int u) {
        for (int v = 0; v < ny; v++) {
            if (v != delY && !used[v] && g[u][v]) {//notice it's g[u][v]
                used[v] = 1;
                if (my[v] == -1 || findY(my[v]))
                    return 1;
            }
        }
        return 0;
    }

    bool findX(int u) {
        for (int v = 0; v < nx; v++) {
            if (v != delX && !used[v] && g[v][u]) {//notice it's g[v][u]
                used[v] = 1;
                if (mx[v] == -1 || findX(mx[v]))
                    return 1;
            }
        }
        return 0;
    }

    //X[i]=1 or Y[i]=1 means it's not a key vertex!!!
    void solve() {
        memset(X, 0, sizeof(X));
        memset(Y, 0, sizeof(Y));
        for (int i = 0; i < nx; i++) {
            if (mx[i] == -1) {
                X[i] = 1;
            } else {
                delY = mx[i];
                memset(used, 0, sizeof(used));
                if (findY(i)) Y[delY] = 1;
            }
        }
        for (int j = 0; j < ny; j++) {
            if (my[j] == -1) {
                Y[j] = 1;
            } else {
                delX = my[j];
                memset(used, 0, sizeof(used));
                if (findX(j)) X[delX] = 1;
            }
        }
    }

}g;

int a, b, n;
int vote[MAXN], idx[MAXN], idy[MAXN];
bool vst[MAXN][MAXN];
void build() {
    scanf("%d%d%d", &a, &b, &n);
    memset(vst, 0, sizeof(vst));
    int nx = 0, ny = 0;
    for (int i = 0; i < n; i++) {
        int x, k, y;
        scanf("%d", &x);
        vote[i] = x;
        if (vote[i] <= a) {
            idx[nx++] = i;
        } else idy[ny++] = i;
        scanf("%d", &k);
        while (k--) {
            scanf("%d", &y);
            vst[i][y] = 1;
        }
    }
    g.init(nx, ny);
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            if (vst[idx[i]][vote[idy[j]]] || vst[idy[j]][vote[idx[i]]]) { 
                g.addEdge(i, j);
            }
        }
    }
}

void work() {
    int ret = g.MaxMatch();
    printf("%d\n", n - ret);
    g.solve();
    vector<int> ans;
    for (int i = 0; i < g.nx; i++)
        if (g.X[i]) ans.PB(vote[idx[i]]);
    for (int j = 0; j < g.ny; j++)
        if (g.Y[j]) ans.PB(vote[idy[j]]);
    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
    printf("%d", ans.size());
    for (int i = 0; i < ans.size(); i++)
        printf(" %d", ans[i]);
    printf("\n");
}

//Hdu 3517 求二分图关键点
int main() {
//    freopen("in.txt", "r", stdin);
    int Test;
    scanf("%d", &Test);
    while (Test--) {
        build();
        work();
    }
    return 0;
}