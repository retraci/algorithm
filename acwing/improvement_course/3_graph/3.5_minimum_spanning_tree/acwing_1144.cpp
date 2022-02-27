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

const int N = 1010;

int n, m;
vector<ti4> a;

int fa[N * N];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    fa[x] = y;
    return true;
}

int get_id(int x, int y) {
    return (x - 1) * m + y - 1;
}

void solve() {
    iota(fa, fa + n * m, 0);
    for (auto [x1, y1, x2, y2] : a) {
        int u = get_id(x1, y1), v = get_id(x2, y2);
        unite(u, v);
    }

    vector<ti3> es;
    for (int j = 1; j <= m; j++) {
        for (int i = 2; i <= n; i++) {
            int u = get_id(i - 1, j), v = get_id(i, j);
            es.push_back({1, u, v});
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            int u = get_id(i, j - 1), v = get_id(i, j);
            es.push_back({2, u, v});
        }
    }

    int ans = 0;
    for (auto [cost, u, v] : es) {
        if (unite(u, v)) ans += cost;
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
        cin >> n >> m;
        int x1, y1, x2, y2;
        while (cin >> x1 >> y1 >> x2 >> y2) {
            a.push_back({x1, y1, x2, y2});
        }
        solve();
    }

    return 0;
}