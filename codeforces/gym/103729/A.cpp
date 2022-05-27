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
#include <cassert>
#include <random>
#include <cmath>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
using al3 = array<ll, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

// region dsu
template<int SZ>
struct Dsu {
    int fa[SZ + 10];

    Dsu() {}

    void init(int _n) {
        iota(fa, fa + _n + 1, 0);
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        fa[tx] = ty;
        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 310;

int n, m, k, ti;
int a[N];
ll f[N][N];
Dsu<N> dsu;

void solve() {
    if (ti == 0) {
        cout << -1 << "\n";
        return;
    }

    for (int t = 1; t <= n; t++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                f[i][j] = min(f[i][j], f[i][t] + f[t][j]);
            }
        }
    }

    dsu.init(n);
    ll ans = 0;
    set<int> st(a + 1, a + k + 1);
    for (int i = 1; i <= n; i++) {
        if (st.count(i)) continue;

        ll mi = 1e18, id = -1;
        for (int j = 1; j <= n; j++) {
            if (j == i || !st.count(j)) continue;

            if (mi > f[i][j]) {
                mi = f[i][j];
                id = j;
            }
        }
        if (id == -1) {
            cout << -1 << "\n";
            return;
        }

        ans = max(ans, 2 * mi);
        dsu.unite(id, i);
    }

    vector<al3> es;
    for (int i = 1; i <= n; i++) {
        if (!st.count(i)) continue;

        for (int j = 1; j <= n; j++) {
            if (!st.count(j)) continue;
            if (f[i][j] == 1e18) continue;

            es.push_back({i, j, f[i][j]});
        }
    }

    sort(es.begin(), es.end(), [](auto &a, auto &b) {
        return a[2] < b[2];
    });
    for (auto [u, v, cost] : es) {
        if (dsu.unite(u, v)) {
            ans = max(ans, cost);
        }
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) cnt += i == dsu.find(i);
    if (cnt != 1) {
        cout << -1 << "\n";
        return;
    }
    cout << (ans + ti - 1) / ti << "\n";
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
        cin >> n >> m >> k >> ti;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i == j) continue;
                f[i][j] = 1e18;
            }
        }

        for (int i = 1; i <= m; i++) {
            int u, v, c;
            cin >> u >> v >> c;
            f[u][v] = f[v][u] = c;
        }
        for (int i = 1; i <= k; i++) cin >> a[i];
        solve();
    }

    return 0;
}