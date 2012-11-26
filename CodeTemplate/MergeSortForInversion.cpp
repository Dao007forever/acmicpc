/*
 * Count inversion pairs by merge sort
 * Notice that the array is a[1], a[2], ..., a[N]
 */
struct MergeSortForInv {
	int n, tot;
	int a[maxn], tmp[maxn];

	void init(int n) {
		this->n = n;
		tot = 0;
	}

	void add(int pos, int num) {
		a[pos] = num;
	}

	void merge(int l, int mid, int r)
	{
	    int i, j, t;
	    t = l;
	    i = l;
	    j = mid + 1;
	    while (t <= r)
	    {
	        if ((i <= mid) && ((j > r) || (a[i] > a[j])))
	        {
	            tmp[t] = a[i];
	            i++;
	        }
	        else
	        {
	            tmp[t] = a[j];
	            j++;
	            tot += i-l;
	        }
	        t++;
	    }
	    for (i = l; i <= r; i++)
	        a[i] = tmp[i];
	}

	void mergesort(int l, int r)
	{
	    int mid;
	    mid = (l + r) / 2;
	    if (l != r)
	    {
	        mergesort(l, mid);
	        mergesort(mid + 1, r);
	        merge(l, mid, r);
	    }
	}

	int solve() {
		mergesort(1, N);//Notice merge a[1]...a[N]!
		return tot;
	}
}mg;
