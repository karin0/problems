#include <cstdio>
#include <map>
#include <cmath>
#include <algorithm>
#define MAXN 100500
#define MAXQ 50100
#define INF 2122222222
// 设 a(i) 为第 i 年的降水量,未知则为 INF
//  state(x, y) 表示 y 年是自 x 年来降水最多的一年
// state(x, y) is true <=> a(x) >= a(y) and 
//                         Any k in (x, y), a(k) < a(y) and // This <=> max1{a(k) | x < k < y} < a(y)
//                         Any k in [x, y], a(k) != INF     //  -|
//               false <=> a(x) != INF and a(y) != INF and a(x) < a(y) or
//                         Exist k in (x, y), a(k) >= a(y) // This <=> max2{a(k) | x < k < y} >= a(y)
//               maybe <=> a(x) == INF or (a(x) >= a(y) (!= INF)), and
//                         Any k in (x, y), a(k) == INF or a(k) < a(y) // This <=> max2{a(k) | x < k < y} < a(y)
/*
struct UnknownRange {
    int ly, ry, yid;
};

UnknownRange unkr[MAXN];
int last_unkr = 0;
*/
struct Year {
    int y, yid, q;
};
bool year_cmp(Year a, Year b) {
    return a.y < b.y;
}
Year years[MAXN];
int qxid[MAXQ], qyid[MAXQ];
int last_year, last_query;

int n, maxk, st[4][MAXN][30], toy[MAXN];
inline void init(int d) {
    // st[i][0] prepared
    for (int k = 1; k <= maxk; ++k)
        for (int i = 1; i + (1 << k) - 1 <= n; ++i)
            st[d][i][k] = std::max(st[d][i][k - 1], st[d][i + (1 << (k - 1))][k - 1]);
}
inline int max(int d, int l, int r) {
    int k = floor(log2(r - l + 1));
    return std::max(st[d][l][k], st[d][r - (1 << k) + 1][k]);
}

inline bool known(int yid) {
    return st[1][yid][0] != INF;
}
/*
inline int get_yid(int y) {
    """
    int flag = 0, yy = y, id;
    while (!to_yid.count(yy)) {
        flag = 1;
        --yy;
    }
    id = to_yid[yy] + flag;
    for (++yy; yy <= y; ++yy) {
        to_yid[yy] = id;
    }
    return id; 
    """
    if (to_yid.count(y))
        return to_yid[y];
    int lb = 1, ub = last_unkr + 1, mid;
    while (ub > lb) { // [lb, ub)
        mid = (lb + ub) >> 1;
        if (unkr[mid].ly > y)
            ub = mid;
        else if (unkr[mid].ry < y)
            lb = mid + 1;
        else
            return unkr[mid].yid;
    }
    printf("[2333]");
    //while (1) {}
    // return to_yid[y];
}
*/
int main() {
    scanf("%d", &n);
    int q, i, x, y, r, qf, y0, r0, last_yid = 1, xid, yid, y_prev, id_prev;
    scanf("%d%d", &y0, &r0);
    y_prev = y0;
    toy[1] = y0;
    st[1][1][0] = st[2][1][0] = r0;
    for (i = 1; i < n; ++i) {
        scanf("%d%d", &y, &r);
        if (y != y_prev + 1) {
            st[1][++last_yid][0] = INF;
            st[2][last_yid][0] = -INF;
            toy[last_yid] = y_prev + 1;
            /*
            unkr[++last_unkr].ly = y_prev + 1;
            unkr[last_unkr].ry = y - 1;
            unkr[last_unkr].yid = last_yid;
            */
        }
        ++last_yid;
        st[1][last_yid][0] = st[2][last_yid][0] = r;
        //printf("Insert %d.\n", y);
        toy[last_yid] = y;
        y_prev = y;
    }
    maxk = floor(log2(last_yid)) + 1;
    init(1);
    init(2);
    scanf("%d", &q);
    for (i = 1; i <= q; ++i) {
        scanf("%d%d", &x, &y); // state(x, y)
        years[2 * i - 1].y = x;
        years[2 * i].y = y;
        years[2 * i - 1].q = years[2 * i].q = i;
    }
    std::sort(years + 1, years + q * 2 + 1, year_cmp);
    y_prev = years[1].y;
    id_prev = std::lower_bound(toy + 1, toy + last_yid + 1, y_prev) - toy;
    if (toy[id_prev] != y_prev)
        --id_prev;
    qxid[years[1].q] = id_prev;
    for (i = 2; i <= 2 * q; ++i) {
        y = years[i].y;
        qf = years[i].q;
        if (y != y_prev) {
            if (y == y_prev + 1)
                yid = id_prev + 1;
            else {
                yid = std::lower_bound(toy + id_prev + 2, toy + last_yid + 1, y) - toy;
                if (toy[yid] > y)
                    --yid;
            }
            y_prev = y;
        } else
            yid = id_prev;
        if (qxid[qf]) {
            if (qxid[qf] > yid) {
                qyid[qf] = qxid[qf];
                qxid[qf] = yid;
            } else {
                qyid[qf] = yid;
            }
        } else
            qxid[qf] = yid;
        id_prev = yid;
    }
    for (i = 1; i <= q; ++i) {
        xid = qxid[i];
        yid = qyid[i];
        if (known(xid)) {
            if (known(yid)) {
                if (st[1][xid][0] >= st[1][yid][0]) {
                    if (max(1, xid + 1, yid - 1) < st[1][yid][0]) {
                        printf("true\n");
                        continue;
                    }
                } else {
                    printf("false\n");
                    continue;
                }
            }
        }
        if (max(2, xid + 1, yid - 1) >= st[1][yid][0]) {
            printf("false\n");
            continue;
        }
        printf("maybe\n");
    }
    return 0;
}
