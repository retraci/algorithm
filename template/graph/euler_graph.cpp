// region 欧拉回路
void dfs(int u) {
    while (~h[u]) {
        int eid = h[u]; h[u] = ne[eid];
        if (vis[eid]) continue;

        auto v = g[eid];
        vis[eid] = vis[eid ^ 1] = 1;
        dfs(v);
    }
}
// endregion
