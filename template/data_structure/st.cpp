// region 区间gcd
template<int SZ>
struct ST {
    using stt = int;

    int n;
    stt st[__lg(SZ) + 1][SZ + 10];

    ST() {}

    // [0, n);
    void init(const vector<stt> &a) {
        n = a.size();

        for (int i = 0; i < n; i++) st[0][i] = a[i];
        int mxb = __lg(n - 1);
        for (int k = 1; k <= mxb; k++) {
            for (int L = 0; L + (1 << k) - 1 < n; L++) {
                st[k][L] = __gcd(st[k - 1][L], st[k - 1][L + (1 << (k - 1))]);
            }
        }
    }

    // [L, R]
    stt qr(int L, int R) {
        assert(L <= R && L >= 0 && R < n);

        int k = __lg(R - L + 1);
        return __gcd(st[k][L], st[k][R - (1 << k) + 1]);
    }
};
// endregion

// region 区间最值
template<int SZ>
struct ST {
    using stt = int;

    int n;
    stt stmi[__lg(SZ) + 1][SZ + 10];
    stt stmx[__lg(SZ) + 1][SZ + 10];

    ST() {}

    // [0, n);
    void init(const vector<stt> &a) {
        n = a.size();

        for (int i = 0; i < n; i++) stmi[0][i] = stmx[0][i] = a[i];
        int mxb = __lg(n - 1);
        for (int k = 1; k <= mxb; k++) {
            for (int L = 0; L + (1 << k) - 1 < n; L++) {
                stmi[k][L] = min(stmi[k - 1][L], stmi[k - 1][L + (1 << (k - 1))]);
                stmx[k][L] = max(stmx[k - 1][L], stmx[k - 1][L + (1 << (k - 1))]);
            }
        }
    }

    // [L, R]
    stt qr_mi(int L, int R) {
        assert(L <= R && L >= 0 && R < n);

        int k = __lg(R - L + 1);
        return min(stmi[k][L], stmi[k][R - (1 << k) + 1]);
    }

    // [L, R]
    stt qr_mx(int L, int R) {
        assert(L <= R && L >= 0 && R < n);

        int k = __lg(R - L + 1);
        return max(stmx[k][L], stmx[k][R - (1 << k) + 1]);
    }
};
// endregion
