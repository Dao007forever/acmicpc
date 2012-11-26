const int maxn = 55;
int dgr[maxn];    //每个点的度
bool cmp(const int &a, const int &b) {
    return dgr[a] < dgr[b];
}
struct MaxClique {
    bool E[maxn][maxn];
    int n;                    //图的所在，需传入
    int c[maxn],stack[maxn],ans,ansStack[maxn];//后俩:答案和可行点
    void init(int n) {
        this->n = n;
        memset(E, 0, sizeof(E));
    }
///    arr中保存了len个点, 程序要筛选出和a相连的点,并保存在newArr
    void intersect(int a,int*arr,int len,int*newArr,int&newLen){
        newLen = 0;
        for(int i = 0; i < len; i ++)
            if(E[a][ arr[i] ])    newArr[newLen ++] = arr[i];
    }
    bool dfs(int *arr, int len, int size) {
        if(len == 0) {
            if(size > ans) {
                ans = size;
                copy(stack, stack+ans, ansStack);
                return true;
            }
            return false;
        }
        int newArr[maxn], newLen, a, b;
        while(len != 0 && size + len > ans) {               //剪枝
            a = arr[0];
            stack[size] = a; //断言a在最大clique里, 装入堆栈
            if(size + c[a] <= ans)                return false;//剪枝
            arr ++;    len --;
            intersect(a, arr, len, newArr, newLen);
            if(dfs(newArr, newLen, size+1))    return true;//剪枝
        }
        return false;
    }
    int solve() {
        memset(dgr, 0, sizeof(dgr));
        for(int i = 0; i < n; i ++)
            for(int j = 0; j < n; j ++)
                if(E[i][j])    dgr[j] ++;
        int arr[maxn], newArr[maxn], newLen;
        for(int i = 0; i < n; i ++)    arr[i] = i;
        sort(arr, arr+n, cmp);                                   //剪枝
        ans = 0;
        for(int i = n-1; i >= 0; i --) {
            intersect(arr[i], arr+i, n-i, newArr, newLen);
            stack[0] = arr[i];//断言arr[i]在最大clique里, 装入堆栈
            dfs(newArr, newLen, 1);
            c[arr[i]] = ans;
        }
        return ans;
    }
}g;
