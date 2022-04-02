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

ull myRand(ull &k1, ull &k2) {
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}

pair<int, int> myRanq(ull &k1, ull &k2, int MAXN) {
    int x = myRand(k1, k2) % MAXN + 1, y = myRand(k1, k2) % MAXN + 1;
    if (x > y)return make_pair(y, x);
    else return make_pair(x, y);
}

const int N = 1e5 + 10;
const int M = 5e5 + 10;

int n, m;
ti3 es[M];

int h[2 * N], ne[2 * N], g[2 * N], edm;
int pa[2 * N], w[2 * N], tt;

int id[2 * N], eula[4 * N], dep[4 * N], cnt;
int st[4 * N][23], lg[4 * N];

int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}

bool unite(int x, int y) {
    int tx = find(x), ty = find(y);
    if (tx == ty) return false;
    pa[tx] = ty;
    return true;
}

void add(int u, int v) {
    g[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void dfs(int u) {
    eula[++cnt] = u, id[u] = cnt;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = g[i];

        dep[v] = dep[u] + 1;
        dfs(v);
        eula[++cnt] = u;
    }
}

void init_st(int rt) {
    dep[rt] = 1;
    dfs(tt);

    lg[0] = -1;
    for (int i = 1; i <= cnt; i++) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= cnt; i++) st[i][0] = eula[i];
    for (int k = 1; (1 << k) <= cnt; k++) {
        for (int i = 1; i + (1 << k) - 1 <= cnt; i++) {
            int a = st[i][k - 1];
            int b = st[i + (1 << (k - 1))][k - 1];

            st[i][k] = dep[a] < dep[b] ? a : b;
        }
    }
}

int lca(int x, int y) {
    int L = id[x], R = id[y];
    if (L > R) swap(L, R);

    int k = lg[R - L + 1];
    int a = st[L][k];
    int b = st[R - (1 << k) + 1][k];

    return dep[a] < dep[b] ? a : b;
}

void init() {
    sort(es + 1, es + m + 1, [](auto &a, auto &b) {
        return get<2>(a) < get<2>(b);
    });
    iota(pa, pa + 2 * n + 1, 0);
    fill(h, h + 2 * n + 1, -1), edm = 0;
    tt = n;
    for (int i = 1; i <= m; i++) {
        auto[u, v, cost] = es[i];
        int tu = find(u), tv = find(v);
        if (tu == tv) continue;

        tt++;
        unite(tu, tt), unite(tv, tt);
        add(tt, tu), add(tt, tv);
        w[tt] = cost;
    }

    init_st(tt);
}

void solve() {
    init();

    int ans = 0;
    ull Q, a1, a2;
    cin >> Q >> a1 >> a2;
    while (Q--) {
        auto[x, y] = myRanq(a1, a2, n);

        int tmp = w[lca(x, y)];
        ans ^= tmp;
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
        for (int i = 1; i <= m; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            es[i] = {u, v, cost};
        }
        solve();
    }

    return 0;
}