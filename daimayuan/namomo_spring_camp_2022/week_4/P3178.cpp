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

const int N = 100010;

int n, m;
int a[N];
int g[2 * N], h[N], ne[2 * N], edm;

ll in[N], out[N], tt;
ll dep[N];
ll b[N];
ll t1[N], t2[N];

void add(ll t[], int id, ll x) {
    for (int i = id; i <= n; i += i & -i) t[i] += x;
}

ll qr(ll t[], int id) {
    ll res = 0;
    for (int i = id; i; i -= i & -i) res += t[i];
    return res;
}

void add(int u, int v) {
    g[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void dfs(int u, int fno, ll s) {
    in[u] = ++tt, b[in[u]] = s;

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = g[i];
        if (v == fno) continue;

        dep[v] = dep[u] + 1;
        dfs(v, u, s + a[v]);
    }

    out[u] = tt;
}

void solve() {
    dep[1] = 1;
    dfs(1, 0, a[1]);

    for (int i = 1; i <= n; i++) add(t1, i, b[i] - b[i - 1]);
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int id, x;
            cin >> id >> x;

            add(t1, in[id], x), add(t1, out[id] + 1, -x);
        } else if (op == 2) {
            int id, x;
            cin >> id >> x;

            add(t2, in[id], x), add(t2, out[id] + 1, -x);
            add(t1, in[id], 1LL * -(dep[id] - 1) * x), add(t1, out[id] + 1, 1LL * (dep[id] - 1) * x);
        } else {
            int id;
            cin >> id;

            ll ans = qr(t1, in[id]) + qr(t2, in[id]) * dep[id];
            cout << ans << "\n";
        }
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
        for (int i = 1; i <= n; i++) cin >> a[i];

        fill(h, h + n + 1, -1), edm = 0;
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
        }

        solve();
    }

    return 0;
}