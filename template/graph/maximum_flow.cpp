// region ek
int n, m, sc, sk;
pii e[M * 2];
int h[N], ne[M * 2], edm;
int mic[N], pe[N];

void add(int u, int v, int cap) {
    e[edm] = {v, cap};
    ne[edm] = h[u], h[u] = edm++;
    e[edm] = {u, 0};
    ne[edm] = h[v], h[v] = edm++;
}

bool bfs() {
    vector<int> vis(n + 1, 0);
    queue<int> que;
    vis[sc] = 1, mic[sc] = 1e9;
    que.push(sc);
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, cap] = e[i];
            if (cap == 0 || vis[v]) continue;
            vis[v] = 1;

            mic[v] = min(mic[u], cap), pe[v] = i;
            if (v == sk) return true;
            que.push(v);
        }
    }

    return false;
}

int ek() {
    int f = 0;
    while (bfs()) {
        f += mic[sk];
        int t = sk;
        while (t != sc) {
            int eid = pe[t];
            e[eid].se -= mic[sk], e[eid ^ 1].se += mic[sk];
            t = e[eid ^ 1].fi;
        }
    }
    return f;
}
// endregion