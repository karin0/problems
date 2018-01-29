double a[13][3], eps = 1e-5;
bool gauss(int n) {
    static int i, j, k, p;
    static double t;
    for (i = 0; i < n; ++i) {
        p = i;
        for (j = i + 1; j < n; ++j)
            if (fabs(a[j][i]) > fabs(a[p][i]))
                p = j;
        if (fabs(a[p][i] < eps))
            return false;
        if (p != i)
            for (j = i; j <= n; ++j)
                std::swap(a[i][j], a[p][j]);
        for (j = 0; j < n; ++j)
            if (i != j) {
                t = a[j][i] / a[i][i];
                for (k = n; k >= i; --k)
                    a[j][k] -= a[i][k] * t;
            }
    }
    return true;
}
