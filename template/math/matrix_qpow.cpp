// region 矩阵
template<int SZ>
struct Mat {
    using matt = int;

    int r, c;
    matt mod;
    matt a[SZ][SZ];

    Mat() {}

    void init(int _r, int _c, int _mod) {
        r = _r, c = _c, mod = _mod;
    }

    inline Mat operator-(const Mat &T) const {
        Mat res;
        res.init(r, c, mod);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                res.a[i][j] = (a[i][j] - T.a[i][j]) % mod;
            }
        }
        return res;
    }

    inline Mat operator+(const Mat &T) const {
        Mat res;
        res.init(r, c, mod);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                res.a[i][j] = (a[i][j] + T.a[i][j]) % mod;
            }
        }
        return res;
    }

    inline Mat operator*(const Mat &T) const {
        Mat res;
        res.init(r, T.c, mod);
        for (int i = 0; i < res.r; i++) {
            for (int j = 0; j < T.c; j++) {
                res.a[i][j] = 0;
                for (int k = 0; k < c; k++) {
                    res.a[i][j] = (res.a[i][j] + a[i][k] * T.a[k][j] % mod) % mod;
                }
            }
        }
        return res;
    }

    inline Mat operator*(matt x) const {
        Mat res;
        res.init(r, c, mod);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                res.a[i][j] = (a[i][j] * x) % mod;
            }
        }
        return res;
    }

    inline Mat operator^(matt x) const {
        assert(r == c);

        Mat res, bas;
        res.init(r, c, mod), bas.init(r, c, mod);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                res.a[i][j] = i == j;
            }
        }
        bas = *this;

        while (x) {
            if (x & 1) res = res * bas;
            bas = bas * bas;
            x >>= 1;
        }
        return res;
    }

    inline bool operator==(const Mat &T) const {
        if (r != T.r || c != T.c) return false;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (a[i][j] != T.a[i][j]) return false;
            }
        }
        return true;
    }

    inline void print() const {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
    }
};
// endregion
