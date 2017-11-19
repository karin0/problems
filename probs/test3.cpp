
//  Created by Sengxian on 6/23/16.
//  Copyright (c) 2016年 Sengxian. All rights reserved.
//  BZOJ 2438 tarjan + 概率
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
inline int ReadInt() {
    static int n, ch;
    n = 0, ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) n = (n << 3) + (n << 1) + ch - '0', ch = getchar();
    return n;
}

const int maxn = 100000 + 3;
vector<int> G[maxn], nG[maxn];
int n, m, dfn[maxn], sccno[maxn], scc_sz[maxn], timestamp = 0, scc_cnt = 0;
int in[maxn];

stack<int> stk;
int dfs(int u) {
    int low = dfn[u] = ++timestamp;
    stk.push(u);
    for (int i = 0; i < (int)G[u].size(); ++i) {
        int v = G[u][i];
        if (!dfn[v]) low = min(low, dfs(v));
        else if (!sccno[v]) low = min(low, dfn[v]);
    }
    if (low == dfn[u]) {
        scc_cnt++;
        do {
            int v = stk.top(); stk.pop();
            scc_sz[scc_cnt]++;
            sccno[v] = scc_cnt;
            if (u == v) break;
        } while (!stk.empty());
    }
    return low;
}


char str[maxn];
int main() {
    int n = ReadInt(), m = ReadInt();
    for (int i = 0; i < m; ++i) {
        int f = ReadInt() - 1, t = ReadInt() - 1;
        G[f].push_back(t);
    }
    timestamp = 0, scc_cnt = 0;
    memset(dfn, 0, sizeof dfn);
    for (int i = 0; i < n; ++i) if (!dfn[i]) dfs(i);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < (int)G[i].size(); ++j) {
            int v = G[i][j];
            if (sccno[i] != sccno[v]) nG[sccno[i]].push_back(sccno[v]), in[sccno[v]]++;
        }
    int cnt = 0;
    for (int i = 1; i <= scc_cnt; ++i) if (in[i] == 0) cnt++;
    for (int i = 1; i <= scc_cnt; ++i)
        if (scc_sz[i] == 1 && in[i] == 0) {
            bool flag = true;
            for (int j = 0; j < (int)nG[i].size(); ++j)
                if (in[nG[i][j]] <= 1) {flag = false; break;}
            if (flag) {cnt--; break;}
        }
    printf("%.6lf\n", (double)(n - cnt) / n);
    return 0;
}
