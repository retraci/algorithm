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

const int N = 3e5 + 10;

int n;
int a[N], d[N], c[N];
int ne[N][44];

void init() {
    for (int i = 1; i <= n - 1; i++) d[i] = a[i + 1] - a[i];
    for (int i = 1; i <= n - 1; i++) c[i] = 0;
    for (int i = 1; i <= n - 1; i++) {
        if (d[i] == 0) continue;

        while (d[i] % 2 == 0) {
            d[i] >>= 1, c[i]++;
        }
    }

    for (int i = n - 1; i >= 1; i--) {
        for (int j = 0; j <= 40; j++) ne[i][j] = -1;
    }

    for (int i = n - 1; i >= 1; i--) {
        ne[i][c[i]] = i + 1;
        for (int j = c[i] + 1; j <= 40; j++) {
            if (ne[i][j - 1] == -1 || ne[i][j - 1] == n) break;
            if (d[i] != d[ne[i][j - 1]]) break;
            ne[i][j] = ne[ne[i][j - 1]][j - 1];
        }
    }
}

void solve() {
    init();

    vector<int> f(n + 1, 1e9);
    f[1] = 0;
    for (int i = 1; i <= n - 1; i++) {
        if (d[i] == 0 && f[i + 1] == 0) {
            f[i] = min(f[i], f[i - 1]);
            continue;
        }

        for (int j = 0; j <= 40; j++) {
            if (ne[i][j] != -1) {
                int k = ne[i][j];
                f[k] = min(f[k], f[i] + 1);
            }
        }
    }

    cout << f[n] + 1 << "\n";
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
        solve();
    }

    return 0;
}