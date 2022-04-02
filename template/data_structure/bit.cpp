// region 区间修改bit
template<int SZ>
struct Bit {
    int n;
    ll tr1[SZ + 1], tr2[SZ + 1];

    Bit() {
        init(SZ);
    }

    void init(int _n) {
        n = _n;
    }

    void add(ll tr[], int id, ll x) {
        for (int i = id; i <= n; i += i & -i) tr[i] += x;
    }

    ll qr(ll tr[], int id) {
        int res = 0;
        for (int i = id; i; i -= i & -i) res += tr[i];
        return res;
    }

    ll get(int id) {
        return (id + 1) * qr(tr1, id) - qr(tr2, id);
    }

    void upd(int L, int R, ll x) {
        add(tr1, L, x), add(tr1, R + 1, -x);
        add(tr2, L, x * L), add(tr2, R + 1, -x * (R + 1));
    }

    ll sum(int L, int R) {
        return get(R) - get(L - 1);
    }
};
// endregion