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

const int N = 2510;

int n, m, k;
int a[N][N];
int f[2][11];

int sum(int x1, int x2, int y1, int y2) {
    if (x1 > x2 || y1 > y2) return -1;
    return a[x2][y2] - a[x1 - 1][y2] - a[x2][y1 - 1] + a[x1 - 1][y1 - 1];
}

ll work(int x1, int x2, int y1, int y2) {
    if (x1 > x2 || y1 > y2) return 0;
    if (x1 == x2 && y1 == y2) {
        return sum(x1, x2, y1, y2) == k;
    }

    ll res = 0;
    if (x2 - x1 > y2 - y1) {
        int mid = x1 + x2 >> 1;
        res += work(x1, mid, y1, y2) + work(mid + 1, x2, y1, y2);

        for (int i = y1; i <= y2; i++) {
            for (int x = 0; x <= k + 1; x++) f[0][x] = x1 - 1, f[1][x] = x2 + 1;
            for (int j = i; j <= y2; j++) {
                for (int x = 0; x <= k + 1; x++) {
                    while (sum(f[0][x] + 1, mid, i, j) >= x) f[0][x]++;
                    while (sum(mid + 1, f[1][x] - 1, i, j) >= x) f[1][x]--;
                }
                for (int x = 0; x <= k; x++) {
                    res += (f[0][x] - f[0][x + 1]) * (f[1][k - x + 1] - f[1][k - x]);
                }
            }
        }
    } else {
        int mid = y1 + y2 >> 1;
        res += work(x1, x2, y1, mid) + work(x1, x2, mid + 1, y2);

        for (int i = x1; i <= x2; i++) {
            for (int x = 0; x <= k + 1; x++) f[0][x] = y1 - 1, f[1][x] = y2 + 1;
            for (int j = i; j <= x2; j++) {
                for (int x = 0; x <= k + 1; x++) {
                    while (sum(i, j, f[0][x] + 1, mid) >= x) f[0][x]++;
                    while (sum(i, j, mid + 1, f[1][x] - 1) >= x) f[1][x]--;
                }
                for (int x = 0; x <= k; x++) {
                    res += (f[0][x] - f[0][x + 1]) * (f[1][k - x + 1] - f[1][k - x]);
                }
            }
        }
    }

    return res;
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
        }
    }

    cout << work(1, n, 1, m) << "\n";
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
        cin >> n >> m >> k;
        string tmp;
        for (int i = 1; i <= n; i++) {
            cin >> tmp;
            for (int j = 1; j <= m; j++) a[i][j] = tmp[j - 1] - '0';
        }
        solve();
    }

    return 0;
}