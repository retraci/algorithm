#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <numeric>
#include <iomanip>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <bitset>

// region general
#define ll long long
#define ld long double
#define ull unsigned long long
#define fi first
#define se second

typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
typedef std::tuple<int, int, int> ti3;
typedef std::tuple<ll, ll, ll> tl3;
typedef std::tuple<int, int, int, int> ti4;
typedef std::tuple<ll, ll, ll, ll> tl4;

inline void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
inline void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}
// endregion
// region grid_delta
namespace grid_delta {
    // 上, 右, 下, 左  |  左上, 右上, 右下, 左下
    const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
}
// endregion

using namespace std;
using namespace grid_delta;

// region ll矩阵
template<int SZ>
struct Mat {
    int r, c;
    ll mod;
    vector<vector<ll>> a;

    inline Mat() {
        r = SZ, c = SZ, mod = 1e9 + 7;
        a = vector<vector<ll>>(SZ, vector<ll>(SZ));
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

    inline Mat operator*(ll x) const {
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

const int N = 22;

ll n, m, mod;
string s;
int ne[N];

Mat<N> xi, f;

void get_ne() {
    for (int i = 2, j = 0; i <= m; i++) {
        while (j && s[i] != s[j + 1]) j = ne[j];
        if (s[i] == s[j + 1]) j++;
        ne[i] = j;
    }
}

void init() {
    get_ne();

    f.init(1, m, mod), xi.init(m, m, mod);
    f.a[0][0] = 1;
    for (int j = 0; j < m; j++) {
        for (int k = 0; k <= 9; k++) {
            int t = j;
            while (t && k + '0' != s[t + 1]) t = ne[t];
            if (k + '0' == s[t + 1]) t++;
            xi.a[j][t]++;
        }
    }
}


void solve() {
    init();

    xi = xi ^ n;
    f = f * xi;

    ll ans = 0;
    for (int j = 0; j < m; j++) {
        ans += f.a[0][j];
        ans %= mod;
    }
    cout << ans << "\n";
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
//    cin >> T;
    while (T--) {
        cin >> n >> m >> mod;
        cin >> s;
        s = ' ' + s;
        solve();
    }

    return 0;
}