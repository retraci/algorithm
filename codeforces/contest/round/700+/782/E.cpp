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

const int N = 1e5 + 10;

// region dsu
template <int SZ>
struct Dsu {
    int n;
    int pa[SZ + 10];

    Dsu() : n(SZ) {
        iota(pa, pa + n + 1, 0);
    }

    void init(int _n) {
        n = _n;
        iota(pa, pa + n + 1, 0);
    }

    int find(int x) {
        return x == pa[x] ? x : pa[x] = find(pa[x]);
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        pa[tx] = ty;
        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
    }
};
// endregion

int n, m;
ti3 es[N];

Dsu<N> dsu[30];

void solve() {
    for (int k = 0; k <= 29; k++) {
        dsu[k].init(n);
    }

    int even[30][n + 1];
    fill(&even[0][0], &even[29][n] + 1, 0);
    for (int i = 1; i <= m; i++) {
        auto [u, v, cost] = es[i];

        for (int k = 0; k <= 29; k++) {
            if (cost >> k & 1) {
                dsu[k].unite(u, v);
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        auto [u, v, cost] = es[i];
        if (cost & 1) continue;

        for (int k = 0; k <= 29; k++) {
            int tx = dsu[k].find(u), ty = dsu[k].find(v);
            even[k][tx] = even[k][ty] = 1;
        }
    }

    int q;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int u, v;
        cin >> u >> v;

        int ans = 2;
        for (int k = 0; k <= 29; k++) {
            if (dsu[k].same(u, v)) ans = 0;
        }
        if (ans == 0) {
            cout << ans << "\n";
            continue;
        }

        for (int k = 1; k <= 29; k++) {
            int tx = dsu[k].find(u);
            if (even[k][tx]) ans = 1;
        }
        cout << ans << "\n";
    }
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
        for (int i = 1; i <= m; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            es[i] = {u, v, cost};
        }
        solve();
    }

    return 0;
}