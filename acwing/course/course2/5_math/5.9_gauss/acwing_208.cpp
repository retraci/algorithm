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

const int N = 33;

// region 异或方程
bitset<N> mat[N];
bitset<N> res;

// r 为方程个数, c 为未知数个数, 无解返回-1, 多解返回自由元个数
// mat[1~n]: 增广矩阵, c + 1 位置为常数
int gauss(int r, int c) {
    int row = 1;
    for (int col = 1; col <= c; col++) {
        for (int i = row; i <= r; i++) {
            if (mat[i][col] == 0) continue;
            swap(mat[row], mat[i]);
            break;
        }
        if (mat[row][col] == 0) continue;

        for (int i = 1; i <= r; i++) {
            if (i != row && mat[i][col]) mat[i] ^= mat[row];
        }
        row++;
    }

    if (row <= r) {
        for (int i = row; i <= r; i++) {
            if (mat[i][c + 1]) return -1;
        }
        return r - row + 1;
    }

    for (int i = 1; i <= r; i++) res[i] = mat[i][c + 1];
    return 0;
}
// endregion

int n, m;
int a[N], b[N];
pii c[N * N];

void init() {
    for (int i = 1; i <= n; i++) mat[i].reset();

    for (int i = 1; i <= n; i++) {
        mat[i][i] = 1;
        mat[i][n + 1] = a[i] ^ b[i];
    }
    for (int i = 1; i <= m; i++) {
        auto [ta, tb] = c[i];
        mat[tb][ta] = 1;
    }
}

void solve() {
    init();

    int ret = gauss(n, n);
    if (ret == -1) {
        cout << "Oh,it's impossible~!!" << "\n";
        return;
    }

    int ans = 1 << ret;
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
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        m = 0;
        int ta, tb;
        while (cin >> ta >> tb, ta || tb) {
            c[++m] = {ta, tb};
        }
        solve();
    }

    return 0;
}