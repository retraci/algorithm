// region dinic 最大流
template<int N, int M>
struct Flow {
    using flowt = int;
    using pit = pair<int, flowt>;
    const flowt INF = 1e9;

    int n;
    pit e[2 * M + 10];
    int h[N + 10], ne[2 * M + 10], edm;
    int nh[N + 10], vis[N + 10];
    flowt d[N + 10];

    Flow() {}

    void init(int _n) {
        n = _n;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v, flowt c1, flowt c2) {
        e[edm] = {v, c1}, ne[edm] = h[u], h[u] = edm++;
        e[edm] = {u, c2}, ne[edm] = h[v], h[v] = edm++;
    }

    bool bfs(int S, int T) {
        queue<int> que;
        fill(d + 1, d + n + 1, -1);

        d[S] = 0;
        que.push(S);
        while (!que.empty()) {
            int u = que.front(); que.pop();

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

    flowt dfs(int u, int T, flowt lit) {
        if (u == T) return lit;

        flowt flow = 0;
        for (int &i = nh[u]; ~i; i = ne[i]) {
            auto &[v, cap] = e[i];
            if (d[v] != d[u] + 1 || cap == 0) continue;

            flowt ret = dfs(v, T, min(cap, lit - flow));
            if (ret == 0) d[v] = -1;
            flow += ret, cap -= ret, e[i ^ 1].se += ret;

            if (lit - flow == 0) break;
        }

        return flow;
    }

    flowt mf(int S, int T) {
        flowt flow = 0;
        while (bfs(S, T)) {
            for (int i = 1; i <= n; i++) nh[i] = h[i];
            while (1) {
                flowt t = dfs(S, T, INF);
                if (t == 0) break;

                flow += t;
            }
        }
        return flow;
    }

    void dfs(int u) {
        vis[u] = 1;

        for (int i = h[u]; ~i; i = ne[i]) {
            auto [v, cap] = e[i];

            if (!vis[v] && cap) dfs(v);
        }
    }

    const vector<int> qr_min_cut(int S, int T) {
        fill(vis, vis + n + 1, 0);
        dfs(S);

        vector<int> res;
        for (int i = 0; i < edm; i += 2) {
            int v = e[i].fi, u = e[i ^ 1].fi;
            if (vis[u] && !vis[v]) res.push_back(i);
        }

        return res;
    }
};
// endregion

// region dinic 费用流
template<int N, int M>
struct Flow {
    using flowt = int;
    using ptt = pair<flowt, flowt>;
    using at3 = array<flowt, 3>;
    const flowt INF = 1e9;

    int n;
    at3 e[2 * M + 10];
    int h[N + 10], ne[2 * M + 10], edm;
    int nh[N + 10], vis[N + 10];
    flowt d[N + 10];

    Flow() {}

    void init(int _n) {
        n = _n;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v, flowt cap, flowt cost) {
        e[edm] = {v, cap, cost}, ne[edm] = h[u], h[u] = edm++;
        e[edm] = {u, 0, -cost}, ne[edm] = h[v], h[v] = edm++;
    }

    bool spfa(int S, int T, int is_mf = 1) {
        static int inq[N + 1] = {0};
        static deque<int> que;
        fill(d + 1, d + n + 1, INF);

        d[S] = 0, inq[S] = 1;
        que.push_back(S);
        while (!que.empty()) {
            int u = que.front(); que.pop_front();
            inq[u] = 0;

            for (int i = h[u]; ~i; i = ne[i]) {
                auto [v, cap, cost] = e[i];
                if (cap == 0) continue;

                if (d[v] > d[u] + cost) {
                    d[v] = d[u] + cost;

                    if (!inq[v]) {
                        inq[v] = 1;
                        if (!que.empty() && d[v] < d[que.front()]) que.push_front(v);
                        else que.push_back(v);
                    }
                }
            }
        }

        // 可行流: cost = d[T] * flow, 若最小费用, 则 d[T] < 0
        if (is_mf) return d[T] != INF;
        else return d[T] != INF && d[T] < 0;
    }

    ptt dfs(int u, int T, flowt lit) {
        if (u == T) return {lit, lit * d[T]};
        vis[u] = 1;

        flowt flow = 0, fco = 0;
        for (int &i = nh[u]; ~i; i = ne[i]) {
            auto &[v, cap, cost] = e[i];
            if (d[v] != d[u] + cost || cap == 0 || vis[v]) continue;

            auto [t1, t2] = dfs(v, T, min(cap, lit - flow));
            if (t1 == 0) d[v] = INF;
            flow += t1, fco += t2, cap -= t1, e[i ^ 1][1] += t1;

            if (lit - flow == 0) break;
        }

        vis[u] = 0;
        return {flow, fco};
    }

    ptt mcmf(int S, int T) {
        flowt flow = 0, fco = 0;
        while (spfa(S, T)) {
            for (int i = 1; i <= n; i++) nh[i] = h[i];
            while (1) {
                auto [t1, t2] = dfs(S, T, INF);
                if (t1 == 0) break;

                flow += t1, fco += t2;
            }
        }

        return {flow, fco};
    }

    ptt mcff(int S, int T) {
        flowt flow = 0, fco = 0;
        while (spfa(S, T, 0)) {
            for (int i = 1; i <= n; i++) nh[i] = h[i];
            while (1) {
                auto [t1, t2] = dfs(S, T, INF);
                if (t1 == 0) break;

                flow += t1, fco += t2;
            }
        }

        return {flow, fco};
    }
};
// endregion

// region primal-dual 费用流
template<int N, int M>
struct Flow {
    using flowt = int;
    using ptt = pair<flowt, flowt>;
    using at3 = array<flowt, 3>;
    const flowt INF = 1e9;

    int n;
    at3 e[2 * M + 10];
    int h[N + 10], ne[2 * M + 10], edm;
    int pre[N + 10];
    flowt d[N + 10], r[N + 10];

    Flow() {}

    void init(int _n) {
        n = _n;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v, flowt cap, flowt cost) {
        e[edm] = {v, cap, cost}, ne[edm] = h[u], h[u] = edm++;
        e[edm] = {u, 0, -cost}, ne[edm] = h[v], h[v] = edm++;
    }

    bool dij(int S, int T) {
        static int vis[N + 10];
        static priority_queue<ptt> que;
        fill(d, d + n + 1, INF);
        fill(vis, vis + n + 1, 0);

        d[S] = 0;
        que.push({0, S});
        while (!que.empty()) {
            auto [_, u] = que.top(); que.pop();
            if (vis[u]) continue;
            vis[u] = 1;

            for (int i = h[u]; ~i; i = ne[i]) {
                auto [v, cap, cost] = e[i];
                if (cap == 0) continue;

                flowt nc = cost + r[u] - r[v];
                if (d[v] > d[u] + nc) {
                    d[v] = d[u] + nc;
                    pre[v] = i;
                    que.push({-d[v], v});
                }
            }
        }

        return d[T] != INF;
    }

    void spfa(int S, int T) {
        static int inq[N + 10] = {0};
        static deque<int> que;
        fill(r + 1, r + n + 1, INF);

        r[S] = 0, inq[S] = 1;
        que.push_back(S);
        while (!que.empty()) {
            int u = que.front(); que.pop_front();
            inq[u] = 0;

            for (int i = h[u]; ~i; i = ne[i]) {
                auto [v, cap, cost] = e[i];
                if (cap == 0) continue;

                if (r[v] > r[u] + cost) {
                    r[v] = r[u] + cost;

                    if (!inq[v]) {
                        inq[v] = 1;
                        if (!que.empty() && r[v] < r[que.front()]) que.push_front(v);
                        else que.push_back(v);
                    }
                }
            }
        }
    }

    ptt mcmf(int S, int T) {
        spfa(S, T);
        flowt flow = 0, fco = 0;
        while (dij(S, T)) {
            for (int i = 1; i <= n; i++) r[i] += d[i];

            flowt minf = INF;
            for (int i = T; i != S; i = e[pre[i] ^ 1][0]) minf = min(minf, e[pre[i]][1]);
            for (int i = T; i != S; i = e[pre[i] ^ 1][0]) {
                e[pre[i]][1] -= minf, e[pre[i] ^ 1][1] += minf;
            }

            flow += minf, fco += minf * r[T];
        }

        return {flow, fco};
    }

    ptt mcff(int S, int T) {
        spfa(S, T);
        flowt flow = 0, fco = 0;
        while (dij(S, T)) {
            for (int i = 1; i <= n; i++) r[i] += d[i];
            // 可行流: cost = d[T] * flow, 若最小费用, 则 d[T] < 0
            if (r[T] >= 0) break;

            flowt minf = INF;
            for (int i = T; i != S; i = e[pre[i] ^ 1][0]) minf = min(minf, e[pre[i]][1]);
            for (int i = T; i != S; i = e[pre[i] ^ 1][0]) {
                e[pre[i]][1] -= minf, e[pre[i] ^ 1][1] += minf;
            }

            flow += minf, fco += minf * r[T];
        }

        return {flow, fco};
    }
};
// endregion
