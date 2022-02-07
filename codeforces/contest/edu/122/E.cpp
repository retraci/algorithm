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
    // 上, 右, 下, 左  |  左上, 右上, 左下, 右下
    const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
    const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 1e5 + 10;
const int M = 310;

int n, m;
tl3 es[M];
ll p, k, a, b, c;
ll vp[N];

int fa[M];

int find(int x) {
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

bool unite(int x, int y) {
    int tx = find(x), ty = find(y);
    if (tx == ty) return false;
    fa[tx] = ty;
    return true;
}

void solve() {
    ll vq[k + 1];
    for (int i = 1; i <= p; i++) vq[i] = vp[i];
    for (int i = p + 1; i <= k; i++) vq[i] = (vq[i - 1] * a + b) % c;
    sort(vq + 1, vq + k + 1);

    set<int> st;
    for (int i = 1; i <= m; i++) {
        auto &[w1, u1, v1] = es[i];
        // 数目左右会变化
        st.insert(w1);
        for (int j = i + 1; j <= m; j++) {
            auto &[w2, u2, v2] = es[j];
            // 边权会变化
            st.insert((w1 + w2) / 2 + 1);
        }
    }

    st.insert(0);
    ll ans = 0, cur = 0, pre = 0, c1 = 0, c2 = 0;
    for (int i = 1; i <= k; i++) {
        ll x = vq[i];
        if (!st.empty() && *st.begin() <= x) {
            while (!st.empty() && *st.begin() <= x) st.erase(st.begin());

            sort(es + 1, es + m + 1, [&](auto &a, auto &b) {
                auto &[w1, u1, v1] = a;
                auto &[w2, u2, v2] = b;
                return abs(w1 - x) < abs(w2 - x);
            });
            iota(fa, fa + n + 1, 0);
            cur = c1 = c2 = 0;
            for (int j = 1; j <= m; j++) {
                auto [w, u, v] = es[j];
                if (!unite(u, v)) continue;
                cur += abs(w - x);
                w <= x ? c1++ : c2++;
            }
        } else {
            cur += (x - pre) * (c1 - c2);
        }

        ans ^= cur, pre = x;
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
            ll u, v, w;
            cin >> u >> v >> w;
            es[i] = {w, u, v};
        }
        cin >> p >> k >> a >> b >> c;
        for (int i = 1; i <= p; i++) cin >> vp[i];
        solve();
    }

    return 0;
}