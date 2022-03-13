// region ll矩阵
template<int SZ>
struct Mat {
    int r, c;
    vector<vector<ll>> a;

    inline Mat(int r = SZ, int c = SZ) : r(r), c(c) {
        a = vector<vector<ll>>(SZ, vector<ll>(SZ));
    }

    inline Mat operator-(const Mat &T) const {
        Mat res(r, c);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                res.a[i][j] = (a[i][j] - T.a[i][j]) % MOD;
            }
        }
        return res;
    }

    inline Mat operator+(const Mat &T) const {
        Mat res(r, c);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                res.a[i][j] = (a[i][j] + T.a[i][j]) % MOD;
            }
        }
        return res;
    }

    inline Mat operator*(const Mat &T) const {
        Mat res(r, T.c);
        for (int i = 0; i < res.r; i++) {
            for (int j = 0; j < T.c; j++) {
                for (int k = 0; k < c; k++) {
                    res.a[i][j] = (res.a[i][j] + a[i][k] * T.a[k][j] % MOD) % MOD;
                }
            }
        }
        return res;
    }

    inline Mat operator*(ll x) const {
        Mat res(r, c);
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                res.a[i][j] = (a[i][j] * x) % MOD;
            }
        }
        return res;
    }

    inline Mat operator^(ll x) const {
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

    inline Mat operator^(ll x) const {
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