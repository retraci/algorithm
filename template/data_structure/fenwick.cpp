// region fenwick
template<int SZ>
struct Fenwick {
    using fwt = int;

    int n;
    fwt tr[SZ + 10];

    Fenwick() {}

    void init(int _n) {
        n = _n;
        fill(tr, tr + n + 1, 0);
    }

    void upd(int id, fwt x) {
        for (int i = id; i <= n; i += i & -i) tr[i] = tr[i] + x;
    }

    fwt qr(int id) {
        fwt res = 0;
        for (int i = id; i; i -= i & -i) res = res + tr[i];
        return res;
    }

    int kth(int x) {
        int pos = 0;
        for (int i = __lg(n); i >= 0; i--) {
            if (pos + (1 << i) <= n && tr[pos + (1 << i)] < x) {
                pos += 1 << i;
                x -= tr[pos];
            }
        }

        return pos + 1;
    }
};
// endregion

// region 区间修改fenwick
template<int SZ>
struct Fenwick {
    using fwt = int;

    int n;
    fwt tr1[SZ + 10], tr2[SZ + 10];

    Fenwick() {}

    void init(int _n) {
        n = _n;
        fill(tr1, tr1 + n + 1, 0);
        fill(tr2, tr2 + n + 1, 0);
    }

    void add(fwt tr[], int id, fwt x) {
        for (int i = id; i <= n; i += i & -i) tr[i] = tr[i] + x;
    }

    fwt query(fwt tr[], int id) {
        fwt res = 0;
        for (int i = id; i; i -= i & -i) res = res + tr[i];
        return res;
    }

    fwt get(int id) {
        return (id + 1) * query(tr1, id) - query(tr2, id);
    }

    void upd(int L, int R, fwt x) {
        add(tr1, L, x), add(tr1, R + 1, -x);
        add(tr2, L, x * L), add(tr2, R + 1, -x * (R + 1));
    }

    fwt qr(int L, int R) {
        return get(R) - get(L - 1);
    }
};
// endregion
