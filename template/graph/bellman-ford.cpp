// region bellman-ford
struct Edge {
    int u, v, w;
};

vector<Edge> es;
int dist[N], dist2[N];

// 强制走 n 条边的最短路
int bellman_ford(int s) {
    memset(dist, 0x3f, sizeof dist);
    dist[s] = 0;
    for (int i = 1; i <= n; i++) {
        memcpy(dist2, dist, sizeof dist2);
        memset(dist, 0x3f, sizeof dist);
        for (auto &[u, v, w] : es) {
            dist[v] = min(dist[v], dist2[u] + w);
            dist[u] = min(dist[u], dist2[v] + w);
        }
    }

    return dist[t];
}
// endregion