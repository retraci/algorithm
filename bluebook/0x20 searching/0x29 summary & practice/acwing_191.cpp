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

typedef tuple<int, int, int, int, int, int, int> ti7;

const int N = 377;

int n;
int g[N][4][4];

int bfs() {
    unordered_map<ti7, int, tuple_hash<ti7>> vis;
    queue<ti7> que;
    vis[{1, 2, 2, 1, 1, 1, 1}] = 1;
    que.push({1, 2, 2, 1, 1, 1, 1});
    while (!que.empty()) {
        auto [d, x, y, s1, s2, s3, s4] = que.front(); que.pop();

        for (int i = 0; i <= 2; i++) {
            for (int k = 0; k < 4; k++) {
                int nd = d + 1;
                int nx = x + dx[k] * i, ny = y + dy[k] * i;
                if (nx >= 1 && nx <= 3 && ny >= 1 && ny <= 3) {
                    if (g[nd][nx][ny] || g[nd][nx][ny + 1] || g[nd][nx + 1][ny] || g[nd][nx + 1][ny + 1]) continue;

                    int ns1 = s1 + 1, ns2 = s2 + 1, ns3 = s3 + 1, ns4 = s4 + 1;
                    if (nx == 1 && ny == 1) ns1 = 0;
                    if (nx == 1 && ny == 3) ns2 = 0;
                    if (nx == 3 && ny == 1) ns3 = 0;
                    if (nx == 3 && ny == 3) ns4 = 0;
                    if (ns1 >= 7 || ns2 >= 7 || ns3 >= 7 || ns4 >= 7) continue;

                    ti7 ns = {nd, nx, ny, ns1, ns2, ns3, ns4};
                    if (!vis.count(ns)) {
                        vis[ns] = 1;
                        que.push(ns);
                        if (nd == n) return 1;
                    }
                }
            }
        }
    }

    return 0;
}

void solve() {
    cout << bfs() << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    auto prework = [&]() -> void {
    };
    prework();

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
//    cin >> T;
    while (cin >> n, n) {
        for (int k = 1; k <= n; k++) {
            for (int i = 1; i <= 4; i++) {
                for (int j = 1; j <= 4; j++) {
                    cin >> g[k][i][j];
                }
            }
        }
        solve();
    }

    return 0;
}