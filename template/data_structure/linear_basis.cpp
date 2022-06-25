// region 线性基 (动态)
template<int SZ>
struct LinearBasis {
    using lbt = ll;

    int mxb;
    lbt bas[SZ + 10];

    LinearBasis() {}

    void init(int _mxb) {
        mxb = _mxb;
        fill(bas, bas + mxb + 1, 0);
    }

    bool ins(lbt x) {
        for (int i = mxb; i >= 0; i--) {
            if (x == 0) break;
            if (~x >> i & 1) continue;

            if (bas[i]) {
                x ^= bas[i];
            } else {
                for (int j = 0; j < i; j++) {
                    if (x >> j & 1) x ^= bas[j];
                }
                for (int j = i + 1; j <= mxb; j++) {
                    if (bas[j] >> i & 1) bas[j] ^= x;
                }
                bas[i] = x;
                return true;
            }
        }

        return false;
    }

    lbt qr_mx() {
        lbt res = 0;
        for (int i = 0; i <= mxb; i++) res ^= bas[i];
        return res;
    }
};
// endregion

// region 线性基 (静态)
template<int SZ>
struct LinearBasis {
    using lbt = ll;

    int mxb, isLinCor;
    lbt bas[SZ + 10];
    vector<lbt> B;

    LinearBasis() {}

    void init(int _mxb) {
        mxb = _mxb, isLinCor = 0;
        fill(bas, bas + mxb + 1, 0);
        B.clear();
    }

    void build(const vector<lbt> &a) {
        for (lbt x : a) isLinCor |= !ins(x);
        for (int i = 0; i <= mxb; i++) {
            if (bas[i]) B.push_back(bas[i]);
        }
    }

    bool ins(lbt x) {
        for (int i = mxb; i >= 0; i--) {
            if (x == 0) break;
            if (~x >> i & 1) continue;

            if (bas[i]) {
                x ^= bas[i];
            } else {
                for (int j = 0; j < i; j++) {
                    if (x >> j & 1) x ^= bas[j];
                }
                for (int j = i + 1; j <= mxb; j++) {
                    if (bas[j] >> i & 1) bas[j] ^= x;
                }
                bas[i] = x;
                return true;
            }
        }

        return false;
    }

    lbt qr_mx() {
        lbt res = 0;
        for (int i = 0; i <= mxb; i++) res ^= bas[i];
        return res;
    }

    lbt kth(lbt k) {
        if (isLinCor) k--;

        lbt res = 0;
        for (lbt b : B) {
            if (k & 1) res ^= b;
            k >>= 1;
        }

        return k == 0 ? res : -1;
    }
};
// endregion
