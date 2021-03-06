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
        assert(id > 0);
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
        assert(id > 0);
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

// region 二维数点
template<int Q, class Fenwick>
struct TwoDimCount {
    using fwt = int;
    using tdct = int;
    using at3 = array<tdct, 3>;
    using at4 = array<tdct, 4>;
    using at5 = array<tdct, 5>;

    int oq;
    at4 oqs[4 * Q + 10];

    TwoDimCount() {}

    // ps[i] = {x, y, w}
    // qs[i] = {qid, x1, x2, y1, y2}
    // m 为第二维的值域, q 为询问总个数
    vector<fwt> work(vector<at3> ps, const vector<at5> &qs, Fenwick &fw, int m, int q) {
        oq = 0;
        for (auto [qid, x1, x2, y1, y2] : qs) {
            oqs[++oq] = {qid, x1 - 1, y2, -1};
            oqs[++oq] = {qid, x1 - 1, y1 - 1, +1};
            oqs[++oq] = {qid, x2, y2, +1};
            oqs[++oq] = {qid, x2, y1 - 1, -1};
        }

        sort(ps.begin(), ps.end(), [](auto &lhs, auto &rhs) {
            return lhs[0] < rhs[0];
        });
        sort(oqs + 1, oqs + oq + 1, [](auto &lhs, auto &rhs) {
            return lhs[1] < rhs[1];
        });

        fw.init(m);
        int u = 0;
        vector<fwt> res(q + 1);
        for (int i = 1; i <= oq; i++) {
            auto [qid, x, y, sgn] = oqs[i];

            while (u < ps.size() && ps[u][0] <= x) fw.upd(ps[u][1], ps[u][2]), u++;
            res[qid] += sgn * fw.qr(y);
        }
        return res;
    }
};
// endregion

// region 三维偏序 cdq
template<int SZ, class Fenwick>
struct Cdq {
    using cdqt = int;
    using at3 = array<cdqt, 3>;
    using at5 = array<cdqt, 5>;

    int n;
    at5 a[SZ + 10];

    Cdq() {}

    // 三维偏序, x1 <= x2 && y1 <= y2 && z1 <= z2, 答案记录在 p2
    void cdq(int L, int R, Fenwick &fw) {
        static at5 tmp[SZ + 10];

        if (L >= R) return;
        int mid = L + R >> 1;
        cdq(L, mid, fw), cdq(mid + 1, R, fw);

        int i = L, j = mid + 1, k = 0;
        while (i <= mid && j <= R) {
            if (a[i][2] <= a[j][2]) fw.upd(a[i][3], a[i][4]), tmp[++k] = a[i++];
            else a[j][0] += fw.qr(a[j][3]), tmp[++k] = a[j++];
        }
        while (i <= mid) fw.upd(a[i][3], a[i][4]), tmp[++k] = a[i++];
        while (j <= R) a[j][0] += fw.qr(a[j][3]), tmp[++k] = a[j++];

        for (int u = L; u <= mid; u++) fw.upd(a[u][3], -a[u][4]);
        for (int u = L, v = 1; u <= R; u++, v++) a[u] = tmp[v];
    }

    // m 为 第三维的值域
    // at5 = {ans, x, y, z, cnt};
    vector<at5> work(const vector<at3> &ps, Fenwick &fw, int m) {
        n = 0;
        for (auto [x, y, z] : ps) a[++n] = {0, x, y, z, 1};
        sort(a + 1, a + n + 1, [](auto &lhs, auto &rhs) {
            auto [ans1, x1, y1, z1, c1] = lhs;
            auto [ans2, x2, y2, z2, c2] = rhs;
            if (x1 != x2) return x1 < x2;
            if (y1 != y2) return y1 < y2;
            return z1 < z2;
        });
        int tt = 1;
        for (int i = 2; i <= n; i++) {
            if (a[i][1] == a[tt][1] && a[i][2] == a[tt][2] && a[i][3] == a[tt][3]) a[tt][4]++;
            else a[++tt] = a[i];
        }

        fw.init(m);
        cdq(1, tt, fw);

        vector<at5> res(tt);
        for (int i = 1; i <= tt; i++) {
            auto [ret, x, y, z, cnt] = a[i];
            // 把相等的也加上
            res[i - 1] = {ret + cnt - 1, x, y, z, cnt};
        }
        return res;
    }
};
// endregion
