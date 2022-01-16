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

using namespace std;

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

// region grid_offset
namespace grid_offset {
    // 上, 右, 下, 左  |  左上, 右上, 左下, 右下
    const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
    const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};
}
// endregion

// region general
#define ll long long
#define fi first
#define se second

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> ti3;
typedef tuple<ll, ll, ll> tl3;
typedef tuple<int, int, int, int> ti4;
typedef tuple<ll, ll, ll, ll> tl4;
// endregion

//using namespace grid_offset;

const int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

const int N = 155;

int n, m;
string g[N];

pii s, t;
int dist[N][N];

void solve() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (g[i][j] == 'K') s = {i, j};
            if (g[i][j] == 'H') t = {i, j};
        }
    }

    memset(dist, -1, sizeof dist);
    queue<pii> que;
    dist[s.fi][s.se] = 0;
    que.push(s);
    while (!que.empty()) {
        auto [x, y] = que.front(); que.pop();

        for (int k = 0; k < 8; k++) {
            int nx = x + dx[k], ny = y + dy[k];
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m && g[nx][ny] != '*') {
                if (dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    que.push({nx, ny});
                }
            }
        }
    }

    cout << dist[t.fi][t.se] << "\n";
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    prework();
    int T = 1;
//    cin >> T;
    while (T--) {
        cin >> m >> n;
        for (int i = 1; i <= n; i++) {
            cin >> g[i];
            g[i] = ' ' + g[i];
        }
        solve();
    }

    return 0;
}