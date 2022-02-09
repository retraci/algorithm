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
#include <cmath>

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

typedef pair<double, double> pdd;

const int N = 19;
const double eps = 1e-8;

int n, m;
pdd vp[N];

vector<int> path[N];

void init() {
    for (int i = 0; i < n; i++) path[i] = {};

    for (int i = 0; i < n; i++) {
        path[i].push_back(1 << i);
        for (int j = 0; j < n; j++) {
            auto &[x1, y1] = vp[i];
            auto &[x2, y2] = vp[j];

            if (fabs(x1 - x2) < eps) continue;
            double a = (y1 / x1 - y2 / x2) / (x1 - x2);
            double b = y1 / x1 - a * x1;
            if (fabs(a - 0) < eps || a > 0) continue;

            int stat = 0;
            for (int k = 0; k < n; k++) {
                auto &[x, y] = vp[k];
                double fy = a * x * x + b * x;
                if (fabs(fy - y) < eps) stat |= 1 << k;
            }
            path[i].push_back(stat);
        }
    }
}

void solve() {
    init();

    int lim = 1 << n;
    int f[lim];
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for (int mask = 0; mask < lim - 1; mask++) {
        int x = 0;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) continue;
            x = i;
            break;
        }

        for (int p : path[x]) {
            int ns = mask | p;
            f[ns] = min(f[ns], f[mask] + 1);
        }
    }

    cout << f[lim - 1] << "\n";
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
        for (int i = 0; i < n; i++) {
            cin >> vp[i].fi >> vp[i].se;
        }
        solve();
    }

    return 0;
}