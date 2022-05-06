// region edmonds
template<int N, int M>
struct Edmonds {
    using ai3 = array<int, 3>;
    const int INF = 1e9;

    int n, m;
    ai3 es[M + 10];
    int in[N + 10];
    int vis[N + 10], co[N + 10], pre[N + 10];

    Edmonds() {}

    void init(int _n, int _m) {
        n = _n, m = _m;
    }

    int work(int rt) {
        int res = 0;

        while (1) {
            fill(in, in + n + 1, INF);

            for (int i = 1; i <= m; i++) {
                auto [u, v, cost] = es[i];

                if (in[v] > cost) {
                    in[v] = cost, pre[v] = u;
                }
            }

            for (int i = 1; i <= n; i++) {
                if (in[i] == INF && i != rt) return -1;
            }

            fill(vis, vis + n + 1, 0);
            fill(co, co + n + 1, 0);
            int cnt = 0;
            for (int i = 1; i <= n; i++) {
                if (i == rt) continue;

                res += in[i];
                int v = i;
                while (v != rt && !co[v] && vis[v] != i) vis[v] = i, v = pre[v];
                if (v != rt && vis[v] == i) {
                    co[v] = ++cnt;
                    for (int t = pre[v]; t != v; t = pre[t]) co[t] = cnt;
                }
            }
            if (cnt == 0) break;

            for (int i = 1; i <= n; i++) {
                if (!co[i]) co[i] = ++cnt;
            }
            int tt = 0;
            for (int i = 1; i <= m; i++) {
                auto [u, v, cost] = es[i];
                if (co[u] == co[v]) continue;

                es[++tt] = {co[u], co[v], cost - in[v]};
            }

            n = cnt, m = tt, rt = co[rt];
        }

        return res;
    }
};
// endregion