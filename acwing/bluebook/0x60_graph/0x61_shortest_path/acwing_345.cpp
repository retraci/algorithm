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

const int N = 210;

int n, m, K, S, E;
ti3 es[N];
int g[N][N];
int f[N][N];

vector<int> lsh;

int get_id(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    for (int i = 1; i <= m; i++) {
        auto [u, v, cost] = es[i];
        lsh.push_back(u), lsh.push_back(v);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    n = lsh.size();

    memset(g, 0x3f, sizeof g);
    for (int i = 1; i <= m; i++) {
        auto [u, v, cost] = es[i];
        u = get_id(u) + 1, v = get_id(v) + 1;
        g[u][v] = g[v][u] = min(g[u][v], cost);
    }
}

void work(int u[][N], int v[][N]) {
    int res[N][N];
    memset(res, 0x3f, sizeof res);

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                res[i][j] = min(res[i][j], u[i][k] + v[k][j]);
            }
        }
    }

    memcpy(u, res, sizeof res);
}

void solve() {
    init();

    memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= n; i++) f[i][i] = 0;
    while (K) {
        if (K & 1) work(f, g);
        work(g, g);
        K >>= 1;
    }

    S = get_id(S) + 1, E = get_id(E) + 1;
    cout << f[S][E] << "\n";
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
        cin >> K >> m >> S >> E;
        for (int i = 1; i <= m; i++) {
            int u, v, cost;
            cin >> cost >> u >> v;
            es[i] = {u, v, cost};
        }
        solve();
    }

    return 0;
}