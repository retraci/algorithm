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

// region 无权的lca
template<int N, class G>
struct Lca {
    int n, mxb;
    int dep[N + 10], fa[__lg(N) + 1][N + 10];

    Lca() {}

    void init(int rt, const G &g) {
        n = g.n, mxb = __lg(n);
        fill(dep, dep + n + 1, -1);

        queue<int> que;
        que.push(rt);
        dep[0] = 0, dep[rt] = 1, fa[0][rt] = 0;
        while (!que.empty()) {
            auto u = que.front(); que.pop();

            for (int i = g.h[u]; ~i; i = g.ne[i]) {
                int v = g.e[i];

                if (dep[v] == -1) {
                    dep[v] = dep[u] + 1;
                    fa[0][v] = u;
                    que.push(v);
                }
            }
        }

        for (int k = 1; k <= mxb; k++) {
            for (int v = 1; v <= n; v++) {
                fa[k][v] = fa[k - 1][fa[k - 1][v]];
            }
        }
    }

    int lca(int x, int y) {
        if (dep[x] < dep[y]) swap(x, y);
        for (int k = mxb; k >= 0; k--) {
            if (dep[fa[k][x]] >= dep[y]) {
                x = fa[k][x];
            }
        }
        if (x == y) return x;

        for (int k = mxb; k >= 0; k--) {
            if (fa[k][x] != fa[k][y]) {
                x = fa[k][x], y = fa[k][y];
            }
        }
        return fa[0][x];
    }
};
// endregion

// region 无权图
template<int N, int M>
struct Graph {
    int n, m;
    int h[N + 10], ne[M * 2 + 10], e[M * 2 + 10], edm;

    Graph() {}

    void init(int _n, int _m) {
        n = _n, m = _m;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }
};
// endregion

const int N = 4e4 + 10;

using G = Graph<N, N>;

int n;
int rt;
G g;
Lca<N, G> lca;

void solve() {
    lca.init(rt, g);

    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;

        int ret = lca.lca(x, y);
        if (ret == x) cout << 1 << "\n";
        else if (ret == y) cout << 2 << "\n";
        else cout << 0 << "\n";
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
        cin >> n;
        g.init(4e4, 4e4);

        for (int i = 1; i <= n; i++) {
            int u, v;
            cin >> u >> v;
            if (v == -1) rt = u;
            else g.add(u, v), g.add(v, u);
        }

        solve();
    }

    return 0;
}