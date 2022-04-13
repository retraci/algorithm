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

const int N = 15;
const ld eps = 1e-5;

// region 普通方程
ld mat[N][N];
ld res[N];

// r 为方程个数, c 为未知数个数, 无解返回-1, 多解返回自由元个数
// mat[1~c]: 增广矩阵, c + 1 位置为常数
int gauss(int r, int c) {
    int row = 1;
    for (int col = 1; col <= c; col++) {
        for (int i = row; i <= r; i++) {
            if (fabs(mat[i][col]) > eps) {
                for (int j = col; j <= c + 1; j++) swap(mat[i][j], mat[row][j]);
                break;
            }
        }
        if (fabs(mat[row][col]) < eps) break;

        for (int i = 1; i <= r; i++) {
            if (i != row && fabs(mat[i][col]) > eps) {
                ld rate = mat[i][col] / mat[row][col];
                for (int j = c + 1; j >= col; j--) {
                    mat[i][j] -= mat[row][j] * rate;
                }
            }
        }
        row++;
    }

    if (row <= r) {
        for (int i = row; i <= r; i++) {
            if (fabs(mat[i][c + 1]) > eps) return -1;
        }
        return r - row + 1;
    }

    for (int i = 1; i <= c; i++) res[i] = mat[i][c + 1] /= mat[i][i];
    return 0;
}
// endregion

int n;
ld a[N][N];

void init() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            mat[i][j] = 2 * (a[i][j] - a[n + 1][j]);
        }

        ld s = 0;
        for (int j = 1; j <= n; j++) {
            s += a[i][j] * a[i][j] - a[n + 1][j] * a[n + 1][j];
        }
        mat[i][n + 1] = s;
    }
}

void solve() {
    init();

    gauss(n, n);
    for (int i = 1; i <= n; i++) {
        cout << fixed << setprecision(3);
        cout << res[i] << " ";
    }
    cout << "\n";
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
        cin >> n;
        for (int i = 1; i <= n + 1; i++) {
            for (int j = 1; j <= n; j++) {
                cin >> a[i][j];
            }
        }

        solve();
    }

    return 0;
}