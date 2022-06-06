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

    int kth(fwt x) {
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

// region 区间修改 fenwick
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

    void upd(fwt tr[], int id, fwt x) {
        for (int i = id; i <= n; i += i & -i) tr[i] = tr[i] + x;
    }

    fwt qr(fwt tr[], int id) {
        fwt res = 0;
        for (int i = id; i; i -= i & -i) res = res + tr[i];
        return res;
    }

    fwt get_presum(int id) {
        return (id + 1) * qr(tr1, id) - qr(tr2, id);
    }

    void upd_range(int L, int R, fwt x) {
        upd(tr1, L, x), upd(tr1, R + 1, -x);
        upd(tr2, L, x * L), upd(tr2, R + 1, -x * (R + 1));
    }

    fwt qr_range(int L, int R) {
        return get_presum(R) - get_presum(L - 1);
    }
};
// endregion

// region 二位数点 fenwick
template<int SZ>
struct Fenwick {
    using fwt = int;
    using ptt = pair<fwt, fwt>;
    using at4 = array<fwt, 4>;

    int n, q;
    fwt tr[SZ + 10];
    vector<ptt> ps;
    vector<at4> qs;

    Fenwick() {}

    void init(int _n, int _q) {
        n = _n, q = _q;
        fill(tr, tr + n + 1, 0);
        ps.clear(), qs.clear();
    }

    void upd(int id, fwt x) {
        for (int i = id; i <= n; i += i & -i) tr[i] = tr[i] + x;
    }

    fwt qr(int id) {
        fwt res = 0;
        for (int i = id; i; i -= i & -i) res = res + tr[i];
        return res;
    }

    void add_point(int x, fwt y) {
        ps.push_back({x, y});
    }

    // qid, 左, 右, 下, 上
    void add_qr(int qid, int x1, int x2, fwt y1, fwt y2) {
        qs.push_back({qid, x1 - 1, y2, -1});
        qs.push_back({qid, x1 - 1, y1 - 1, +1});
        qs.push_back({qid, x2, y2, +1});
        qs.push_back({qid, x2, y1 - 1, -1});
    }

    vector<fwt> get_ans() {
        sort(ps.begin(), ps.end(), [](auto &a, auto &b) {
            return a.fi < b.fi;
        });
        sort(qs.begin(), qs.end(), [](auto &a, auto &b) {
            return a[1] < b[1];
        });

        int u = 0;
        vector<fwt> ans(q + 1);
        for (auto [qid, x, y, sgn] : qs) {
            while (u < ps.size() && ps[u].fi <= x) upd(ps[u].se, 1), u++;
            ans[qid] += sgn * qr(y);
        }
        return ans;
    }
};
// endregion
