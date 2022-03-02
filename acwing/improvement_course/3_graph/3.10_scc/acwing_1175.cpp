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

// region hash_func
template<typename TT>
struct tuple_hash {
    size_t operator()(TT const &tt) const {
        return std::hash<TT>()(tt);
    }
};

template<class T>
inline void hash_combine(std::size_t &seed, T const &v) {
    seed ^= tuple_hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename T>
inline void hash_val(std::size_t &seed, const T &val) {
    hash_combine(seed, val);
}

template<typename T, typename... Types>
inline void hash_val(std::size_t &seed, const T &val, const Types &... args) {
    hash_combine(seed, val);
    hash_val(seed, args...);
}

template<typename... Types>
inline std::size_t hash_val(const Types &... args) {
    std::size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

template<class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
struct HashValueImpl {
    void operator()(size_t &seed, Tuple const &tuple) const {
        HashValueImpl<Tuple, Index - 1>{}(seed, tuple);
        hash_combine(seed, std::get<Index>(tuple));
    }
};

template<class Tuple>
struct HashValueImpl<Tuple, 0> {
    void operator()(size_t &seed, Tuple const &tuple) const {
        hash_combine(seed, std::get<0>(tuple));
    }
};

template<typename... TT>
struct tuple_hash<std::tuple<TT...>> {
    size_t operator()(std::tuple<TT...> const &tt) const {
        size_t seed = 0;
        HashValueImpl<std::tuple<TT...>>{}(seed, tt);
        return seed;
    }
};

struct pair_hash {
    template<class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const {
        return hash_val(p.first, p.second);
    }
};
// endregion

const int N = 1e5 + 10;
const int M = 1e6 + 10;

int n, m, mod;
int g[2 * M], ne[2 * M], h1[N], h2[N], edm;

int dfn[N], low[N], ti;
vector<int> stk;
int ins[N];
int co[N], sz[N], scc;

void add(int h[], int u, int v) {
    g[edm] = v;
    ne[edm] = h[u], h[u] = edm++;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++ti;
    stk.push_back(u), ins[u] = 1;

    for (int i = h1[u]; ~i; i = ne[i]) {
        int v = g[i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (low[u] == dfn[u]) {
        scc++;
        int t;
        do {
            t = stk.back(); stk.pop_back(), ins[t] = 0;
            co[t] = scc;
            sz[scc]++;
        } while (t != u);
    }
}

void init() {
    fill(dfn, dfn + n + 1, 0);
    for (int u = 1; u <= n; u++) {
        if (!dfn[u]) tarjan(u);
    }

    unordered_set<pii, pair_hash> st;
    fill(h2, h2 + scc + 1, -1);
    for (int u = 1; u <= n; u++) {
        for (int i = h1[u]; ~i; i = ne[i]) {
            int v = g[i];
            int su = co[u], sv = co[v];
            if (su == sv || st.count({su, sv})) continue;

            add(h2, su, sv);
            st.insert({su, sv});
        }
    }
}

void solve() {
    init();

    vector<int> f(scc + 1, 0), c(scc + 1, 0);
    for (int u = scc; u >= 1; u--) {
        if (c[u] == 0) {
            f[u] = sz[u];
            c[u] = 1;
        }

        for (int i = h2[u]; ~i; i = ne[i]) {
            int v = g[i];

            if (f[v] < f[u] + sz[v]) {
                f[v] = f[u] + sz[v];
                c[v] = c[u];
            } else if (f[v] == f[u] + sz[v]) {
                c[v] += c[u];
                c[v] %= mod;
            }
        }
    }

    int mx = *max_element(f.begin() + 1, f.end());
    int ans = 0;
    for (int i = 1; i <= scc; i++) {
        if (f[i] == mx) {
            ans += c[i];
            ans %= mod;
        }
    }
    cout << mx << "\n";
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
        cin >> n >> m >> mod;
        fill(h1, h1 + n + 1, -1), edm = 0;

        for (int i = 1; i <= m; i++) {
            int u, v;
            cin >> u >> v;
            add(h1, u, v);
        }

        solve();
    }

    return 0;
}