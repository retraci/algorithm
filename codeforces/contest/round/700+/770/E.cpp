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
    // ???, ???, ???, ???  |  ??????, ??????, ??????, ??????
    const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
    const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 3e5 + 10;

int n;
vector<vector<int>> va;

vector<int> lsh;

ti3 g[2 * N];
int h[N], ne[N], tt;
int du[N];
int vis[2 * N];
queue<int> que[N];

vector<string> ans;

void add(int u, int v, int type, int idx) {
    g[tt] = {v, type, idx};
    ne[tt] = h[u], h[u] = tt;
    que[u].push(tt);
    du[v]++;

    tt++;
}

int get_id(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
}

void dfs(int u) {
    while (!que[u].empty()) {
        int ed_id = que[u].front(); que[u].pop();
        if (vis[ed_id]) continue;
        vis[ed_id] = vis[ed_id ^ 1] = 1;
        auto &[v, type, idx] = g[ed_id];
        if (type) ans[-lsh[v - 1]][idx] = 'R';
        else ans[-lsh[u - 1]][idx] = 'L';
        dfs(v);
    }
}

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int x : va[i]) lsh.push_back(x);
    }
    for (int i = 1; i <= n; i++) lsh.push_back(-i);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());

    int nl = lsh.size();

    fill(h + 1, h + nl + 1, -1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < va[i].size(); j++) {
            int u = get_id(-i), v = get_id(va[i][j]);
            add(u, v, 0, j), add(v, u, 1, j);
        }
    }

    for (int i = 1; i <= nl; i++) {
        if (du[i] & 1) {
            cout << "NO" << "\n";
            return;
        }
    }

    ans = vector<string>(n + 1);
    for (int i = 1; i <= n; i++) ans[i] = string(va[i].size(), 'L');
    for (int i = 1; i <= nl; i++) {
        dfs(i);
    }

    cout << "YES" << "\n";
    for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
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
        va = vector<vector<int>>(n + 1);
        for (int i = 1; i <= n; i++) {
            int m;
            cin >> m;
            va[i].resize(m);
            for (int j = 0; j < m; j++) cin >> va[i][j];
        }
        solve();
    }

    return 0;
}