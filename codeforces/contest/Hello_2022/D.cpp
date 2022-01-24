#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

// region hash_func
namespace hash_func {
    template<typename TT>
    struct tuple_hash {
        size_t operator()(TT const &tt) const {
            return std::hash<TT>()(tt);
        }
    };

    template<class T>
    inline void hash_combine(std::size_t &seed, T const &v) {
        seed ^= hash_func::tuple_hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
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

    struct pair_hash {
        template<class T1, class T2>
        std::size_t operator()(const std::pair<T1, T2> &p) const {
            return hash_val(p.first, p.second);
        }
    };
}
// endregion
// region grid_delta
namespace grid_delta {
    // 上, 右, 下, 左  |  左上, 右上, 左下, 右下
    const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
    const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};
}
// endregion
// region general
#define ll long long
#define fi first
#define se second

typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
typedef std::tuple<int, int, int> ti3;
typedef std::tuple<ll, ll, ll> tl3;
typedef std::tuple<int, int, int, int> ti4;
typedef std::tuple<ll, ll, ll, ll> tl4;
// endregion

using namespace std;
using namespace grid_delta;

const int N = 255;

int n;
ll g[2 * N][2 * N];

void solve() {
    ll ans = 0;
    for (int i = n; i < 2 * n; i++) {
        for (int j = n; j < 2 * n; j++) {
            ans += g[i][j];
        }
    }

    ll mi = min({
        g[n - 1][n],
        g[n][n - 1],
        g[n - 1][2 * n - 1],
        g[n][0],
        g[0][2 * n - 1],
        g[2 * n - 1][0],
        g[0][n],
        g[2 * n - 1][n - 1]
    });

    ans += mi;
    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < 2 * n; i++) {
            for (int j = 0; j < 2 * n; j++) {
                cin >> g[i][j];
            }
        }
        solve();
    }

    return 0;
}