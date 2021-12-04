#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

/*----------------------------------------*/

template<int SZ>
struct Mat {
    int r, c;
    ll a[SZ + 1][SZ + 1];

    inline Mat(int r = 0, int c = 0) : r(r), c(c) {
        memset(a, 0, sizeof a);
    }

    inline Mat operator-(const Mat &T) const {
        Mat res(r, c);
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                res.a[i][j] = (a[i][j] - T.a[i][j]) % MOD;
            }
        }
        return res;
    }

    inline Mat operator+(const Mat &T) const {
        Mat res(r, c);
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                res.a[i][j] = (a[i][j] + T.a[i][j]) % MOD;
            }
        }
        return res;
    }

    inline Mat operator*(const Mat &T) const {
        Mat res(r, T.c);
        for (int i = 1; i <= res.r; i++) {
            for (int j = 1; j <= T.c; j++) {
                for (int k = 1; k <= c; k++) {
                    res.a[i][j] = (res.a[i][j] + a[i][k] * T.a[k][j] % MOD) % MOD;
                }
            }
        }
        return res;
    }

    inline Mat operator*(ll x) const {
        Mat res(r, c);
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                res.a[i][j] = (a[i][j] * x) % MOD;
            }
        }
        return res;
    }

    inline Mat operator^(ll x) const {
        Mat res(r, c), bas(r, c);
        for (int i = 1; i <= r; i++) res.a[i][i] = 1;
        memcpy(bas.a, a, sizeof a);

        while (x) {
            if (x & 1) res = res * bas;
            bas = bas * bas;
            x >>= 1;
        }
        return res;
    }

    inline bool operator==(const Mat &T) const {
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                if (a[i][j] != T.a[i][j]) return false;
            }
        }
        return true;
    }

    inline void print() const {
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
    }
};