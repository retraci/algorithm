// region 无权图
template<int N, int M>
struct Graph {
    int n, m;
    int h[N + 10], ne[M * 2 + 10], e[M * 2 + 10], edm;

    Graph() {}

    void init(int _n, int _m) {
        n = _n, m = _m;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }
};
// endregion

// region 带权图
template<int N, int M>
struct Graph {
    using gt = int;
    using pit = pair<int, gt>;

    int n, m;
    pit e[M * 2 + 10];
    int h[N + 10], ne[M * 2 + 10], edm;

    Graph() {}

    void init(int _n, int _m) {
        n = _n, m = _m;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v, gt cost) {
        e[edm] = {v, cost}, ne[edm] = h[u], h[u] = edm++;
    }
};
// endregion
