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

const int N = 2010;

int n, m, k;
int a[N][N];

int sub(int x, int y) {
    return (x - y + k) % k;
}

ll calc1(int r) {
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        if (r == i) continue;

        res += sub(a[r][1], a[i][1]);
    }
    for (int j = 1; j <= m; j++) res += sub(k, a[r][j]);

    return res;
}

ll calc2(int c) {
    ll res = 0;
    for (int j = 1; j <= m; j++) {
        if (c == j) continue;

        res += sub(a[1][c], a[1][j]);
    }
    for (int i = 1; i <= n; i++) res += sub(k, a[i][c]);

    return res;
}

void solve() {
    int flag = 0;
    for (int i = 2; i <= n; i++) {
        int tmp = sub(a[1][1], a[i][1]);
        for (int j = 2; j <= m; j++) {
            if (sub(a[1][j], a[i][j]) != tmp) flag = 1;
        }
    }
    for (int j = 2; j <= m; j++) {
        int tmp = sub(a[1][1], a[1][j]);
        for (int i = 2; i <= n; i++) {
            if (sub(a[i][1], a[i][j]) != tmp) flag = 1;
        }
    }
    if (flag) {
        cout << -1 << "\n";
        return;
    }

    ll ans = 1e18;
    for (int i = 1; i <= n; i++) ans = min(ans, calc1(i));
    for (int i = 1; i <= m; i++) ans = min(ans, calc2(i));

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
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n >> m >> k;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) cin >> a[i][j];
        }
        solve();
    }

    return 0;
}