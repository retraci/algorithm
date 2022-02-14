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
    // 上, 右, 下, 左  |  左上, 右上, 左下, 右下
    const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
    const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};
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

const int N = 3e5 + 10;

int n, m;
int va[N];
pii vb[N];
unordered_set<pii, pair_hash> st;

ll work(vector<int> &vec1, vector<int> &vec2) {
    sort(vec1.begin(), vec1.end()), sort(vec2.begin(), vec2.end());

    priority_queue<ti3> pq;
    unordered_map<pii, int, pair_hash> vis;
    pq.push({vec1.back() + vec2.back(), vec1.size() - 1, vec2.size() - 1});
    while (!pq.empty()) {
        auto [v, id1, id2] = pq.top(); pq.pop();
        int x1 = vec1[id1], x2 = vec2[id2];
        if (x1 != x2 && !st.count({x1, x2})) return v;
        if (vis[{id1, id2}]) continue;
        vis[{id1, id2}] = 1;

        if (id1 - 1 >= 0) pq.push({vec1[id1 - 1] + vec2[id2], id1 - 1, id2});
        if (id2 - 1 >= 0) pq.push({vec1[id1] + vec2[id2 - 1], id1, id2 - 1});
    }

    return 0;
}

void solve() {
    unordered_map<int, int> cnt;
    for (int i = 1; i <= n; i++) cnt[va[i]]++;
    st = {};
    for (int i = 1; i <= m; i++) {
        auto &[x, y] = vb[i];
        st.insert({x, y}), st.insert({y, x});
    }

    unordered_map<int, vector<int>> mp;
    for (auto &[v, c] : cnt) mp[c].push_back(v);

    ll ans = 0;
    for (auto &[c1, vec1] : mp) {
        for (auto &[c2, vec2] : mp) {
            if (c1 > c2) continue;
            ll ret = work(vec1, vec2);
            ans = max(ans, (c1 + c2) * ret);
        }
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
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> va[i];
        for (int i = 1; i <= m; i++) cin >> vb[i].fi >> vb[i].se;
        solve();
    }

    return 0;
}