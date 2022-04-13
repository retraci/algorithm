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

typedef tuple<double, int, int> tdi;

const int N = 510;

int n, m;
pii a[N];

int fa[N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    fa[x] = y;
    return true;
}

double get(pii p1, pii p2) {
    auto [x1, y1] = p1;
    auto [x2, y2] = p2;
    double dx = x1 - x2, dy = y1 - y2;
    return sqrt(dx * dx + dy * dy);
}

void solve() {
    if (m >= n) {
        cout << "0.00" << "\n";
        return;
    }

    vector<tdi> es;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            es.push_back({get(a[i], a[j]), i, j});
        }
    }

    sort(es.begin(), es.end());
    iota(fa, fa + n + 1, 0);
    int cnt = n;
    double ans = 0;
    for (auto [cost, u, v] : es) {
        if (unite(u, v)) {
            ans = cost;
            if (--cnt == m) break;
        }
    }

    cout << fixed << setprecision(2);
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i].fi >> a[i].se;
        solve();
    }

    return 0;
}