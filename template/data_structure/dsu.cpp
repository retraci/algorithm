// region dsu
template <int SZ>
struct Dsu {
    int n;
    int pa[SZ + 10];

    Dsu() : n(SZ) {
        iota(pa, pa + n + 1, 0);
    }

    void init(int _n) {
        n = _n;
        iota(pa, pa + n + 1, 0);
    }

    int find(int x) {
        return x == pa[x] ? x : pa[x] = find(pa[x]);
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        pa[tx] = ty;
        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
    }
};
// endregion