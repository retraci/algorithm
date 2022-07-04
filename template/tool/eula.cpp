// region 欧拉序1
// 应用: lca 转 rmq问题, 维护 eula序 中dep最小的点
void dfs(int u, const G &g) {
    eula[++cnt] = u, id[u] = cnt;

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (dep[v] != -1) continue;

        dep[v] = dep[u] + 1;
        dfs(v, g);
        eula[++cnt] = u;
    }
}
// endregion

// region 欧拉序2
// 如果 u, v 有祖先关系 && ein[u] < ein[v] => [ein[u], ein[v]] 就是 u -> v 的路径
// 如果 u, v 无祖先关系 && ein[u] < ein[v] => [eout[u], ein[v]] + lca(u, v) 就是 u -> v 的路径
// 应用: 树上莫队
void dfs(int u, int fno) {
    eula[++cnt] = u, ein[u] = cnt;

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        dfs(v, u);
    }

    eula[++cnt] = u, eout[u] = cnt;
}
// endregion