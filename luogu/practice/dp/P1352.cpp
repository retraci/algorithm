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

const int N = 6e3 + 10;

int n;
int a[N];

int g[N], h[N], ne[N], edm;
int du[N];

int f[N][2];

void add(int u, int v) {
    g[edm] = v;
    ne[edm] = h[u], h[u] = edm++;
}

void dfs(int u) {
    f[u][1] = a[u];
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = g[i];

        dfs(v);

        f[u][1] += f[v][0];
        f[u][0] += max(f[v][0], f[v][1]);
    }
}

void solve() {
    int rt = 1;
    for (int i = 1; i <= n; i++) {
        if (du[i] == 0) rt = i;
    }

    dfs(rt);

    cout << max(f[rt][0], f[rt][1]) << "\n";
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
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> v >> u;
            add(u, v);
            du[v]++;
        }

        solve();
    }

    return 0;
}