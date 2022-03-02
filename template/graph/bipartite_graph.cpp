// region 染色判断二分图
int co[N];

bool dfs(int u, int color, int mid) {
    co[u] = color;

    for (int i = h[u]; ~i; i = ne[i]) {
        auto [cost, v] = g[i];
        if (cost <= mid) continue;

        if (!co[v]) {
            if (!dfs(v, -color, mid)) return false;
        } else {
            if (co[v] != -color) return false;
        }
    }

    return true;
}

bool check(int mid) {
    fill(co, co + n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (!co[i]) {
            if (!dfs(i, 1, mid)) return false;
        }
    }
    return true;
}
// endregion

// region 匈牙利算法
// 最大匹配 = 最小点覆盖 = N - 最大独立集 = N - 最小路径点覆盖(最小路径重复点覆盖)
int match[N], st[N];

bool dfs(int u) {
    for (int v = 1; v <= n; v++) {
        if (st[v] || !g[u][v]) continue;
        st[v] = 1;

        int t = match[v];
        if (!t || dfs(t)) {
            match[v] = u;
            return true;
        }
    }

    return false;
}
// endregion