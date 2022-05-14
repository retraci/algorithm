// region 矩阵
template<int SZ>
struct Mat {
    using matt = int;
    const matt mod = 1e9 = 7;
    
    int r, c;
    matt mod;
    vector<vector<matt>> a;

    inline Mat() {
        r = SZ, c = SZ;
        a = vector<vector<matt>>(SZ, vector<matt>(SZ));
    }

    inline void init(int _r, int _c, int _mod) {
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
        Mat res, bas;
        res.init(r, c, mod), bas.init(r, c, mod);
        for (int i = 0; i < r; i++) res.a[i][i] = 1;
        bas.a = a;

        while (x) {
            if (x & 1) res = res * bas;
            bas = bas * bas;
            x >>= 1;
        }
        return res;
    }

    inline bool operator==(const Mat &T) const {
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

// region 泛型矩阵
template<typename T, int SZ>
struct Mat {
    int r, c;
    vector<vector<T>> a;

    inline Mat(int r = SZ, int c = SZ) : r(r), c(c) {
        a = vector<vector<T>>(SZ, vector<T>(SZ));
    }

    inline Mat operator-(const Mat &rhs) const {
        Mat res(r, c);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                res.a[i][j] = a[i][j] - rhs.a[i][j];
            }
        }
        return res;
    }

    inline Mat operator+(const Mat &rhs) const {
        Mat res(r, c);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                res.a[i][j] = a[i][j] + rhs.a[i][j];
            }
        }
        return res;
    }

    inline Mat operator*(const Mat &rhs) const {
        Mat res(r, rhs.c);
        for (int i = 0; i < res.r; i++) {
            for (int j = 0; j < rhs.c; j++) {
                for (int k = 0; k < c; k++) {
                    res.a[i][j] = res.a[i][j] + a[i][k] * rhs.a[k][j];
                }
            }
        }
        return res;
    }

    inline Mat operator*(T x) const {
        Mat res(r, c);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                res.a[i][j] = a[i][j] * x;
            }
        }
        return res;
    }

    inline Mat operator^(matt x) const {
        Mat res(r, c), bas(r, c);
        for (int i = 0; i < r; i++) res.a[i][i] = 1;
        bas.a = a;

        while (x) {
            if (x & 1) res = res * bas;
            bas = bas * bas;
            x >>= 1;
        }
        return res;
    }

    inline bool operator==(const Mat &rhs) const {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                if (a[i][j] != rhs.a[i][j]) return false;
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
