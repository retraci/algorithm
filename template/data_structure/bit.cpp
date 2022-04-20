// region bit
template<int SZ>
struct Bit {
    int n;
    ll tr[SZ + 10];

    Bit() {
        init(SZ);
    }

    void init(int _n, ll v = 0) {
        n = _n;
        fill(tr, tr + n + 1, v);
    }

    void upd(int id, ll x) {
        for (int i = id; i <= n; i += i & -i) tr[i] += x;
    }

    ll qr(int id) {
        ll res = 0;
        for (int i = id; i; i -= i & -i) res += tr[i];
        return res;
    }
};
// endregion

// region 区间修改bit
template<int SZ>
struct Bit {
    int n;
    ll tr1[SZ + 10], tr2[SZ + 10];

    Bit() {
        init(SZ);
    }

    void init(int _n, ll v = 0) {
        n = _n;
        fill(tr1, tr1 + n + 1, v);
        fill(tr2, tr2 + n + 1, v);
    }

    void add(ll tr[], int id, ll x) {
        for (int i = id; i <= n; i += i & -i) tr[i] += x;
    }

    ll query(ll tr[], int id) {
        ll res = 0;
        for (int i = id; i; i -= i & -i) res += tr[i];
        return res;
    }

    ll get(int id) {
        return (id + 1) * query(tr1, id) - query(tr2, id);
    }

    void upd(int L, int R, ll x) {
        add(tr1, L, x), add(tr1, R + 1, -x);
        add(tr2, L, x * L), add(tr2, R + 1, -x * (R + 1));
    }

    ll qr(int L, int R) {
        return get(R) - get(L - 1);
    }
};
// endregion