
bool np[N];
int pri[N], pcnt;
int sieve(const int n) {

    for (i = 2; i <= n; ++i) {
        if (!np[i])
            pri[++pcnt] = i;
        for (j = 1; j <= pcnt && (v = (ll)i * pri[j]) <= n; ++j) {
            np[v] = true;
            if (i % pri[j] == 0)
                break;
        }
    }
}
