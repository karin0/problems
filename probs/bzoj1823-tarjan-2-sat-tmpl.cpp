#include <cstdio>
#include <algorithm>
#include <stack>

const int MAXV = 210, MAXE = 2010;

int nv, ne, adj[MAXV], to[MAXE], next[MAXE], belong[MAXV];

inline int opp(int x) {
    return (x & 1) ? (x + 1) : (x - 1);
}
inline void add_edge(int u, int v, int e) {
    to[e] = v;
    next[e] = adj[u];
    adj[u] = e;
}
int tim, dfn[MAXV], low[MAXV], scnt;
bool ins[MAXV];
std::stack<int> sta;
inline bool tarjan(int u) {
    int v, e;
    dfn[u] = ++tim;
    low[u] = tim;
    sta.push(u);
    ins[u] = true;
    for (e = adj[u]; e; e = next[e]) {
        v = to[e];
        if (!dfn[v]) {
            if (!tarjan(v))
                return false;
            low[u] = std::min(low[u], low[v]);
        } else if (ins[v])
            low[u] = std::min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++scnt;
        do {
            v = sta.top();
            sta.pop();
            ins[v] = false;
            belong[v] = scnt;
            if (belong[opp(v)] == scnt)
                return false;
        } while (u != v);
    }
    return true;
}

inline bool check() {
    for (int i = 1; i <= nv; ++i)
        if (!dfn[i] && !tarjan(i))
            return false;
    return true;
}

inline void reset() {
    std::fill(adj + 1, adj + nv + 1, 0);
    std::fill(to + 1, to + ne + 1, 0);
    std::fill(next + 1, next + ne + 1, 0);
    std::fill(belong + 1, belong + nv + 1, 0);
    std::fill(low + 1, low + nv + 1, 0);
    std::fill(dfn + 1, dfn + nv + 1, 0);
    std::fill(ins + 1, ins + nv + 1, false);
    tim = 0;
    scnt = 0;
    while (!sta.empty())
        sta.pop();
}

inline int read() {
    static char ch;
    static int no;
    ch = 0;
    while (ch != 'm' && ch != 'h')
        ch = getchar();
    scanf("%d", &no);
    return (no << 1) - (ch == 'm'); // h(x) := 2 * x, m(x) := 2 * x - 1
}
int main() {
    int kase, t, n, m, i, j, k;
    scanf("%d", &t);
    for (kase = 1; ; ++kase) {
        scanf("%d%d", &n, &m);
        nv = n << 1;
        ne = m << 1;
        for (i = 1; i <= m; ++i) {
            j = read();
            k = read();
            add_edge(opp(j), k, i);
            add_edge(opp(k), j, m + i);
        }

        puts(check() ? "GOOD" : "BAD");
        if (kase == t)
            return 0;
        // putchar('\n');
        reset();
    }
    
    return 0;
}
