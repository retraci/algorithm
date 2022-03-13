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
#include <cmath>

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

// region 矩阵
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

const int N = 1e3 + 10;

int t, k;
ld C[N][N];
ld a[N], b[N];
Mat<ld, 2> xi(2, 2), x(2, 1);

void init() {
    ld tmp = pow((ld) 0.5, t);
    for (int i = 0; i <= t; i++) {
        a[i] = 1.0 * C[t][i] * tmp;
    }
    for (int i = 0; i <= t; i++) {
        b[i] = a[i] * i;
    }

    for (int i = 1; i <= t; i++) {
        a[i] += a[i - 1];
        b[i] += b[i - 1];
    }
}

bool check(int mid) {
    Mat tmp = xi ^ mid;
    Mat ret = tmp * x;
    return ceil(ret.a[0][0]) == ceil(x.a[0][0]);
}

void solve() {
    t--;
    init();

    x.a = {{0},
           {1}};
    int c = 0;
    while (c < k) {
        int j2 = max((ld) 1.0, ceil(x.a[0][0]));
        ld ta = a[j2 - 1], tb = b[t] - b[j2 - 1];
        xi.a = {{ta, tb},
                 {0, 1}};

        int left = 1, right = k - c;
        while (left < right) {
            int mid = left + right + 1 >> 1;
            if (check(mid)) left = mid;
            else right = mid - 1;
        }

        xi = xi ^ left;
        x = xi * x;
        c += left;
    }

    cout << fixed << setprecision(6);
    cout << x.a[0][0] + 1 << "\n";
}

void prework() {
    for (int i = 0; i <= 1e3; i++) C[i][0] = 1;
    for (int i = 1; i <= 1e3; i++) {
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
        }
    }
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
        cin >> t >> k;
        solve();
    }

    return 0;
}