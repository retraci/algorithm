// region 欧拉回路
int e[M * 2], ne[M * 2], h[N], edm;

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void dfs(int u) {
    while (~h[u]) {
        int eid = h[u]; h[u] = ne[eid];
        if (vis[eid]) continue;

        auto v = e[eid];
        vis[eid] = vis[eid ^ 1] = 1;
        dfs(v);
    }
}
// endregion
