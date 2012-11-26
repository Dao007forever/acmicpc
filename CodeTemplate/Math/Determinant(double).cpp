double Determinant() {
    LL det = 1;
    for (int i = 0; i < n; det = det * mat[i][i] % mod, i++)
        for (int j = i + 1; j < n; j++) {
            while(mat[j][i]) {
                for (int k = n - 1; k >= i; k--)
                    mat[i][k] = (mat[i][k] - (mat[i][i] / mat[j][i]) * mat[j][k]) % mod;
                for (int k = i; k < n; k++)
                    swap(mat[i][k], mat[j][k]);
                det = -det;
            }
        }
    if (det < 0) det += mod;
    return (int)det;
}
