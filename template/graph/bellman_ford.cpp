// region bellman-ford
vector<ti3> es;
int d1[N], d2[N];

// 强制走 n 条边的最短路
int bellman_ford(int s) {
    memset(d1, 0x3f, sizeof d1);
    d1[s] = 0;
    for (int i = 1; i <= n; i++) {
        memcpy(d2, d1, sizeof d2);
        memset(d1, 0x3f, sizeof d1);
        for (auto &[u, v, w] : es) {
            d1[v] = min(d1[v], d2[u] + w);
            d1[u] = min(d1[u], d2[v] + w);
        }
    }

    return d1[t];
}
// endregion
