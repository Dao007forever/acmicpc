int Gauss(int n, int m) {
	int Rank = 0;
	for (int j = 0, i; j < m && Rank < n; j++) {	
		for (i = Rank; i < n && abs(equ[i][j]) < eps; i++);
		if (i >= n)		
			continue;
		if (i != Rank) {
				for (int k = j; k <= m; k++)
					swap(equ[Rank][k], equ[i][k]);
			}
		for (int k = m; k >= j; k--)
			equ[Rank][k] /= equ[Rank][j];
			
		for (i = Rank + 1; i < n; i++) if (abs(equ[i][j]) > eps) {
			for (int k = m; k >= j; k--)
				equ[i][k] = equ[i][k] - equ[Rank][k] * equ[i][j];
		}
		Rank++;
	}
//如果保证一定有唯一解，下面两行可以删了，之后for循环里直接另key(行主元)=i
	for (int i = n - 1; i >= Rank; i--) if (abs(equ[i][m]) > eps)
		return 0;
	for (int i = Rank - 1, pre = m, key; i >= 0; i--) {
		for (key = 0; abs(equ[i][key]) < eps; key++);
		for (int k = key + 1; k < pre; k++)
			X[k] = 0.0;		//自由元
		double sum = equ[i][m];
		for (int k = key + 1; k < m; k++)
			sum -= X[k] * equ[i][k];
		X[pre = key] = sum;
	}
	return 1;
}