// region ek
template<int N, int M>
struct Flow {
    using flowt = int;
    using pif = std::pair<int, flowt>;
    const flowt INF = 1e9;

    int n;
    pif e[M * 2];
    int h[N], ne[M * 2], edm;
    flowt incf[N], pe[N];

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
        vector<int> vis(n + 1, 0);
        queue<int> que;
        vis[S] = 1, incf[S] = INF;
        que.push(S);
        while (!que.empty()) {
            auto u = que.front(); que.pop();

            for (int i = h[u]; ~i; i = ne[i]) {
                auto [v, cap] = e[i];
                if (cap == 0 || vis[v]) continue;
                vis[v] = 1;

                incf[v] = min(incf[u], cap), pe[v] = i;
                if (v == T) return true;
                que.push(v);
            }
        }

        return false;
    }

    flowt max_flow(int S, int T) {
        flowt flow = 0;
        while (bfs(S, T)) {
            flow += incf[T];
            int t = T;
            while (t != S) {
                int eid = pe[t];
                e[eid].se -= incf[T], e[eid ^ 1].se += incf[T];
                t = e[eid ^ 1].fi;
            }
        }

        return flow;
    }
};
// endregion

// region dinic
template<int N, int M>
struct Flow {
    using flowt = int;
    using pif = std::pair<int, flowt>;
    const flowt INF = 1e9;

    int n;
    pif e[2 * M + 10];
    int h[N + 10], ne[2 * M + 10], edm;
    int d[N + 10], nh[N + 10], vis[N + 10];

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
        fill(d + 1, d + n + 1, -1);
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

    flowt max_flow(int S, int T) {
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

// region ek 费用流
template<int N, int M>
struct Flow {
    using flowt = int;
    using pff = pair<flowt, flowt>;
    using af3 = array<flowt, 3>;
    const int INF = 1e9;

    int n;
    af3 e[M * 2 + 10];
    int h[N + 10], ne[M * 2 + 10], edm;
    int d[N + 10], pe[N + 10];
    flowt incf[N + 10];

    Flow() {}

    void init(int _n) {
        n = _n;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v, flowt cap, flowt cost) {
        e[edm] = {v, cap, cost}, ne[edm] = h[u], h[u] = edm++;
        e[edm] = {u, 0, -cost}, ne[edm] = h[v], h[v] = edm++;
    }

    bool spfa(int S, int T) {
        fill(d, d + n + 1, INF);
        fill(incf, incf + n + 1, 0);
        vector<int> inq(n + 1, 0);

        deque<int> que;
        inq[S] = 1, d[S] = 0, incf[S] = INF;
        que.push_back(S);
        while (!que.empty()) {
            auto u = que.front(); que.pop_front();
            inq[u] = 0;

            for (int i = h[u]; ~i; i = ne[i]) {
                auto [v, cap, cost] = e[i];
                if (cap == 0) continue;

                if (d[v] > d[u] + cost) {
                    d[v] = d[u] + cost;
                    incf[v] = min(incf[u], cap), pe[v] = i;

                    if (!inq[v]) {
                        inq[v] = 1;
                        if (!que.empty() && d[v] < d[que.front()]) que.push_front(v);
                        else que.push_back(v);
                    }
                }
            }
        }

        return incf[T] > 0;
    }

    pff max_flow_cost(int S, int T) {
        flowt flow = 0, dis = 0;
        while (spfa(S, T)) {
            flow += incf[T], dis += incf[T] * d[T];
            int t = T;
            while (t != S) {
                int eid = pe[t];
                e[eid][1] -= incf[T], e[eid ^ 1][1] += incf[T];
                t = e[eid ^ 1][0];
            }
        }

        return {flow, dis};
    }
};
// endregion

// region dinic 费用流
template<int N, int M>
struct Flow {
    using flowt = int;
    using pff = pair<flowt, flowt>;
    using af3 = array<flowt, 3>;
    const flowt INF = 1e9;

    int n;
    af3 e[2 * M + 10];
    int h[N + 10], ne[2 * M + 10], edm;
    int d[N + 10], nh[N + 10], vis[N + 10];

    Flow() {}

    void init(int _n) {
        n = _n;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v, flowt cap, flowt cost) {
        e[edm] = {v, cap, cost}, ne[edm] = h[u], h[u] = edm++;
        e[edm] = {u, 0, -cost}, ne[edm] = h[v], h[v] = edm++;
    }

    bool spfa(int S, int T) {
        fill(d + 1, d + n + 1, INF);
        vector<int> inq(n + 1, 0);

        deque<int> que;
        d[S] = 0, inq[S] = 1;
        que.push_back(S);
        while (!que.empty()) {
            auto u = que.front(); que.pop_front();
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

        return d[T] != INF;
    }

    pff dfs(int u, int T, flowt lit) {
        if (u == T) return {lit, lit * d[T]};
        vis[u] = 1;

        flowt flow = 0, dis = 0;
        for (int &i = nh[u]; ~i; i = ne[i]) {
            auto &[v, cap, cost] = e[i];
            if (d[v] != d[u] + cost || cap == 0 || vis[v]) continue;

            auto [t1, t2] = dfs(v, T, min(cap, lit - flow));
            if (t1 == 0) d[v] = INF;
            flow += t1, dis += t2, cap -= t1, e[i ^ 1][1] += t1;

            if (lit - flow == 0) break;
        }

        vis[u] = 0;
        return {flow, dis};
    }

    pff max_flow_cost(int S, int T) {
        flowt flow = 0, dis = 0;
        while (spfa(S, T)) {
            for (int i = 1; i <= n; i++) nh[i] = h[i];
            while (1) {
                auto [t1, t2] = dfs(S, T, INF);
                if (t1 == 0) break;

                flow += t1, dis += t2;
            }
        }

        return {flow, dis};
    }
};
// endregion