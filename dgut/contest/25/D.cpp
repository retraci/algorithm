#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;

#define ll long long

const ll MOD = 20211114;

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

ll n, k;

Mat<50> xi;
Mat<50> f;

void init() {
    xi = Mat<50>(k, k);

    for (int i = 1; i <= k; i++) {
        xi.a[1][i] = 1;
    }
    for (int i = 2; i <= k; i++) {
        xi.a[i][i - 1] = 1;
    }

    f = Mat<50>(k, 1);
    f.a[1][1] = 1;
}

void solve() {
    init();

    xi = xi ^ n;
    f = xi * f;

    cout << f.a[1][1] << endl;
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    solve();

    return 0;
}