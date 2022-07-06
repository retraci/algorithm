// region dsu
template<int SZ>
struct Dsu {
    int fa[SZ + 10];

    Dsu() {}

    void init(int _n) {
        iota(fa, fa + _n + 1, 0);
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        fa[tx] = ty;
        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
    }
};
// endregion

// region 可撤销 dsu
template<int SZ>
struct Dsu {
    vector<pii> his_fa, his_sz;
    int fa[SZ + 10], sz[SZ + 10];

    Dsu() {}

    void init(int _n) {
        iota(fa, fa + _n + 1, 0);
        fill(sz, sz + _n + 1, 1);
        his_fa.clear();
        his_sz.clear();
    }

    int find(int x) {
        while (x != fa[x]) x = fa[x];
        return x;
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        if (sz[tx] > sz[ty]) swap(tx, ty);

        his_sz.push_back({ty, sz[ty]});
        sz[ty] += sz[tx];
        his_fa.push_back({tx, fa[tx]});
        fa[tx] = ty;

        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
    }

    void rollback(int h) {
        while (his_fa.size() > h) {
            fa[his_fa.back().fi] = his_fa.back().se;
            his_fa.pop_back();
            sz[his_sz.back().fi] = his_sz.back().se;
            his_sz.pop_back();
        }
    }

    int his() {
        return his_fa.size();
    }

    int size(int x) {
        int tx = find(x);
        return sz[tx];
    }
};
// endregion
