void build(Node *a[], cint n) {
    static Node *sta[N];
    vecurr = vepool;
    std::sort(a + 1, a + n + 1, cmp);
    Node **top = sta;
    *++top = &g[1];
    rep (i, 1, n) {
        Node *u = a[i];
        Node *l = lca(u, *top);
        while (top > sta + 1 && *(top - 1)->dep > l->dep)
            varc(sta[top - 1], *(top - 1)), --top;
        if (*top != l) varc(l, *top);
        --top;
        if (*top != l) *++top = l;
        *++top = u;
    }
    while (top > sta + 1)
        varc(*(top - 1), *top), --top;

}
