#include <cstdio>
#include <stack>

const int MAXN = 10005, MAXM = 50005;

int nv, ne;
int adj[MAXN], from[MAXM], to[MAXM], next[MAXM];
inline void arc(int u, int v, int e) {
    from[e] = u;
    to[e] = v;
    next[e] = adj[u];
    adj[u] = e;
}
int scnt, ind[MAXN], belong[MAXN];
bool non[MAXN];
inline void tarjan(int u) {
    static int dfn[MAXN], low[MAXN], tim;
    static std::stack<int> sta;
    static bool ins[MAXN];
    
    dfn[u] = ++tim;
    low[u] = tim;
    sta.push(u);
    ins[u] = true;
    int e, v;
    for (e = adj[u]; e; e = next[e]) {
        v = to[e];
        if (!dfn[v])
            tarjan(v), low[u] = std::min(low[u], low[v]);
        else if (ins[v])
            low[u] = std::min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++scnt;
        do {
            v = sta.top();
            sta.pop();
            ins[v] = false;
            belong[v] = scnt;
        } while (u != v);
    }
}

int main() {
    int i, u, v, sans = 0, ans = 0;
    scanf("%d%d", &nv, &ne);
    for (i = 1; i <= ne; ++i) {
        scanf("%d%d", &u, &v);
        arc(u, v, i); // Chong Bian
    }
    tarjan(1);
    for (i = 1; i <= ne; ++i)
        if (belong[from[i]] != belong[to[i]])
            non[belong[from[i]]] = true; // printf("[%d]", i);
    for (i = 1; i <= scnt; ++i) {
        if (!non[i]) {
            if (sans) {
                puts("0");
                return 0;
            } else
                sans = i;
        }
    }
    for (i = 1; i <= nv; ++i)
        if (belong[i] == sans)
            ++ans; //printf("(%d)", i);
    printf("%d\n", ans);

    return 0;
}
