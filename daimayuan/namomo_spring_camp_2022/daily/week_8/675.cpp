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

const int N = 310;

int n;
int a[N];
ld f[N][N][N];

ld dfs(int i, int j, int k) {
    if (i < 0 || j < 0 || k < 0) return 0;
    if (i == 0 && j == 0 && k == 0) return 0;
    if (f[i][j][k] != -1) return f[i][j][k];

    ld p0 = 1.0 * (n - (i + j + k)) / n;
    ld p1 = 1.0 * i / n;
    ld p2 = 1.0 * j / n;
    ld p3 = 1.0 * k / n;
    ld res = (1
              + p1 * dfs(i - 1, j, k)
              + p2 * dfs(i + 1, j - 1, k)
              + p3 * dfs(i, j + 1, k - 1)) / (1 - p0);
    return f[i][j][k] = res;
}

void solve() {
    int c1 = 0, c2 = 0, c3 = 0;
    for (int i = 1; i <= n; i++) {
        c1 += a[i] == 1;
        c2 += a[i] == 2;
        c3 += a[i] == 3;
    }

    fill(&f[0][0][0], &f[300][300][300] + 1, -1);

    cout << fixed << setprecision(10);
    cout << dfs(c1, c2, c3) << "\n";
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}