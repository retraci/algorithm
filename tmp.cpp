#include <bits/stdc++.h>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

// region 矩阵
template<int SZ>
struct Mat {
    using matt = double;

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
                    res.a[i][j] = (res.a[i][j] + a[i][k] * T.a[k][j]);
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

    inline Mat operator^(ll x) const {
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

    inline void set(const vector<vector<matt>> &_a) {
        for (int i = 0; i < _a.size(); i++) {
            for (int j = 0; j < _a[i].size(); j++) {
                a[i][j] = _a[i][j];
            }
        }
    }

    inline void print() const {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                cout << fixed << setprecision(10);
                cout << a[i][j] << " \n"[j == c - 1];
            }
        }
    }
};
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

Mat<2> t, it, lam, x;

void solve() {
}

void prework() {
    t.init(2, 2, -1);
    it.init(2, 2, -1);
    lam.init(2, 2, -1);
    x.init(2, 1, -1);

    t.set({{2, 1 + sqrt(5)},
           {2, 1 - sqrt(5)}});
    it.set({{0.13819660112502103037, 0.36180339887497896963},
            {0.22360679774995793928, -0.22360679774995793928}});
    lam.set({{(1 + sqrt(5)) / 2, 0},
             {0, (1 - sqrt(5)) / 2}});
    x.set({{1},
           {1}});

    t.print();
    auto y = t * (lam) * it * x;

    y.print();
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--) {
        solve();
    }

    return 0;
}