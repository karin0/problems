#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 5000003;
int rk[N], sa[N], ht[N], nn;
void build(char *str, int n, int m) {
    static int fir[N], sec[N], tmp[N], cnt[N], i, l;
    static bool uni;
    std::fill(sa, sa + nn, 0);
    std::fill(rk, rk + nn, 0);
    std::fill(cnt, cnt + nn, 0);
    std::fill(tmp, tmp + nn, 0);
    ++n;
    str[n - 1] = 0;
    std::fill(cnt, cnt + m, 0);
    for (i = 0; i < n; ++i)
        ++cnt[str[i]];
    for (i = 1; i < m; ++i)
        cnt[i] += cnt[i - 1];
    for (i = 0; i < n; ++i)
        rk[i] = cnt[str[i]] - 1;
    for (l = 1; l < n; l <<= 1) {
        for (i = 0; i < n; ++i)
            fir[i] = rk[i], sec[i] = (i + l < n) ? rk[i + l] : 0;
        std::fill(cnt, cnt + n, 0);
        for (i = 0; i < n; ++i)
            ++cnt[sec[i]];
        for (i = 1; i < n; ++i)
            cnt[i] += cnt[i - 1];
        for (i = n - 1; i >= 0; --i)
            tmp[--cnt[sec[i]]] = i;
        std::fill(cnt, cnt + n, 0);
        for (i = 0; i < n; ++i)
            ++cnt[fir[i]];
        for (i = 1; i < n; ++i)
            cnt[i] += cnt[i - 1];
        for (i = n - 1; i >= 0; --i)
            sa[--cnt[fir[tmp[i]]]] = tmp[i];
        uni = true;
        rk[sa[0]] = 0;
        for (i = 1; i < n; ++i) {
            rk[sa[i]] = rk[sa[i - 1]];
            if (fir[sa[i]] == fir[sa[i - 1]] && sec[sa[i]] == sec[sa[i - 1]])
                uni = false;
            else
                ++rk[sa[i]];
        }
        if (uni)
            break;
    }
    --n;
}

char s[N], t[N], rt[N], fin[N], ans[N], ch;
int main() {
    static int i, n, k, cc;
    scanf("%s%d", s, &k);
    nn =  n = strlen(s);
    nn += 3;


	if (k == 1) {
		for (i = 0; i < n; ++i)
			t[i] = s[i];
		std::reverse(t, t + n);
        if (strcmp(s, t) < 0)
            puts(s);
        else
            puts(t);
        return 0;
	} else if (k == 2) {
        strcpy(ans, s);
        for (i = 1; i < n; ++i) {
            ch = s[i];
            s[i] = 0;
            strcpy(t, s);
            strcpy(rt, s);
            std::reverse(rt, rt + i);
            if (strcmp(t, rt) < 0)
                strcpy(fin, t);
            else
                strcpy(fin, rt);
            s[i] = ch;
            strcpy(t, s + i);
            strcpy(rt, s + i);
            std::reverse(rt, rt + strlen(s + i));
            if (strcmp(t, rt) < 0)
                strcpy(fin + i, t);
            else
                strcpy(fin + i, rt);
            if (strcmp(fin, ans) < 0)
                strcpy(ans, fin);
        }
        puts(ans);
        return 0;
    }
    std::reverse(s, s + n);
    while (n > 0 && cc < k) {
        // printf("\nDo %d\n", n);
        build(s, n, 128);
        // printf("\nsa[1] = %d\n", sa[1]);
        for (i = sa[1]; i < n; ++i) {
            putchar(s[i]);
            s[i] = 0;
        }
        n = sa[1];
        ++cc;
    }
    // printf("\nOver\n");
    if (n > 0) {
        for (i = 0; i < n; ++i)
            rt[i] = t[i] = s[i];
        rt[n] = t[n] = 0;
        std::reverse(rt, rt + n);
        if (strcmp(t, rt) < 0)
            puts(t);
        else
            puts(rt);
    }

    return 0;
}

