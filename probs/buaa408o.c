#include <stdio.h>
#include <stdlib.h>

#define rep(i_, s_, t_) for (i_ = s_; i_ <= t_; ++i_)
#define re(i_, s_, t_) for (i_ = s_; i_ < t_; ++i_)

#define N 1002

int typ[N], pos[N], vel[N], nxt[N], vis[11000001];

#define same(p, q) (((p > 0) && (q > 0)) || ((p < 0) && (q < 0)))

int cnt, r;
// int tim;
void update(int dt) {
    int i, j, k, *va, *vb;
    while (dt--) {
        // ++tim;
        rep (i, 1, cnt) {
            int x = (pos[i] += vel[i]);
            nxt[i] = 0;
            // printf("cnt = %d, tim = %d, pos[%d] = %d, vel[%d] = %d, typ = %d\n", cnt, tim, i, pos[i], i, vel[i], typ[i]);
            if (x == 0 || x == r)
                vel[i] = -vel[i];
            else {
                while (x < 0)
                    puts("TLE");
                while (x > r)
                    puts("TLE");
                if (vis[x])
                    nxt[vis[x]] = i;
                vis[x] = i;
            }
        }
        rep (i, 1, cnt) if (pos[i] > 0 && pos[i] < r) {
            vis[pos[i]] = 0;
            j = nxt[i];
            if (!j)
                continue;
            nxt[i] = 0;
            va = &vel[i];
            vb = &vel[j];
            k = nxt[j];
            if (k) {
                nxt[j] = 0;
                *va = -*va;
                *vb = -*vb;
                while (1) {
                    int t = nxt[k];
                    vel[k] = -vel[k];
                    if (t)
                        nxt[k] = 0, k = t;
                    else
                        break;                    
                }
            } else {
                if (same(*va, *vb)) {
                    if (abs(*va) > abs(*vb))
                        *va = -*va;
                    else
                        *vb = -*vb;
                } else {
                    *va = -*va;
                    *vb = -*vb;
                }
            }
        }
    }
}

                /* if (a > cnt || b > cnt) {
                    puts("WA");<=                    exit(0);
                } */
                // printf("cnt = %d, tim = %d, pos[%d] = %d, vel[%d] = %d\n", cnt, tim, i, pos[i], i, vel[i]);

#define print(x) (flag ? printf(" %d", x) : (flag = 1, printf("%d", x)))
#define swap(a, b) (t = a, a = b, b = t)

int main() {
    while (1)
        puts("出题人傻逼");
    int v0, v1, n, tl, i, j;
    int flag = 0;
    scanf("%d%d%d%d%d", &v0, &v1, &r, &n, &tl);
    for (cnt = 0; cnt < n; ++cnt) {
        int s;
        scanf("%d%d", &typ[cnt + 1], &s);
        update(s);
        vel[cnt + 1] = typ[cnt + 1] ? v1 : v0;
    }
    update(tl);

    rep (i, 1, n)
        re (j, 1, n)
            if (pos[j] > pos[j + 1]) {
                int t;
                swap(pos[j], pos[j + 1]);
                swap(typ[j], typ[j + 1]);
            }

    rep (i, 1, n)
        if (!typ[i])
            print(pos[i]);
    putchar('\n');
    flag = 0;
    rep (i, 1, n)
        if (typ[i])
            print(pos[i]);
    putchar('\n');

    return 0;
}