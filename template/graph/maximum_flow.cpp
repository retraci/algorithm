// region ek
int n, m, sc, sk;
pii e[M * 2];
int h[N], ne[M * 2], edm;
int mic[N], pe[N];

void add(int u, int v, int c1, int c2) {
    e[edm] = {v, c1}, ne[edm] = h[u], h[u] = edm++;
    e[edm] = {u, c2}, ne[edm] = h[v], h[v] = edm++;
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

// region dinic 整数
int n, m, S, T;
pii e[2 * M];
int h[N], ne[2 * M], edm;
int d[N], nh[N], tt;

void add(int u, int v, int c1, int c2) {
    e[edm] = {v, c1}, ne[edm] = h[u], h[u] = edm++;
    e[edm] = {u, c2}, ne[edm] = h[v], h[v] = edm++;
}

bool bfs() {
    fill(d + 1, d + tt + 1, -1);
    queue<int> que;
    d[S] = 0;
    que.push(S);
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, cap] = e[i];
            if (d[v] != -1 || cap == 0) continue;

            d[v] = d[u] + 1;
            if (v == T) return true;
            que.push(v);
        }
    }

    return false;
}

int dfs(int u, int lit) {
    if (u == T) return lit;

    int flow = 0;
    for (int &i = nh[u]; ~i; i = ne[i]) {
        auto &[v, cap] = e[i];
        if (d[v] != d[u] + 1 || cap == 0) continue;

        int ret = dfs(v, min(cap, lit - flow));
        if (ret == 0) d[v] = -1;
        flow += ret, cap -= ret, e[i ^ 1].se += ret;

        if (lit - flow == 0) break;
    }

    return flow;
}

ll dinic() {
    ll flow = 0;
    while (bfs()) {
        for (int i = 1; i <= tt; i++) nh[i] = h[i];
        int tmp;
        while (tmp = dfs(S, 1e9)) flow += tmp;
    }
    return flow;
}
// endregion

// region dinic 浮点
using pid = std::pair<int, double>;

int n, m, S, T;
pid e[2 * M];
int h[N], ne[2 * M], edm;
int d[N], nh[N], tt;

void add(int u, int v, double c1, double c2) {
    e[edm] = {v, c1}, ne[edm] = h[u], h[u] = edm++;
    e[edm] = {u, c2}, ne[edm] = h[v], h[v] = edm++;
}

bool bfs() {
    fill(d + 1, d + tt + 1, -1);
    queue<int> que;
    d[S] = 0;
    que.push(S);
    while (!que.empty()) {
        auto u = que.front(); que.pop();

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, cap] = e[i];
            if (d[v] != -1 || cap == 0) continue;

            d[v] = d[u] + 1;
            if (v == T) return true;
            que.push(v);
        }
    }

    return false;
}

double dfs(int u, double lit) {
    if (u == T) return lit;

    double flow = 0;
    for (int &i = nh[u]; ~i; i = ne[i]) {
        auto &[v, cap] = e[i];
        if (d[v] != d[u] + 1 || cap == 0) continue;

        double ret = dfs(v, min(cap, lit - flow));
        if (ret == 0) d[v] = -1;
        flow += ret, cap -= ret, e[i ^ 1].se += ret;

        if (lit - flow == 0) break;
    }

    return flow;
}

double dinic() {
    double flow = 0;
    while (bfs()) {
        for (int i = 1; i <= tt; i++) nh[i] = h[i];
        double tmp;
        while (tmp = dfs(S, 1e9)) flow += tmp;
    }
    return flow;
}
// endregion