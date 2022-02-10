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

void solve() {
}

const int N = 15, M = 9;
const double INF = 1e9;

int n, m = 8;
int s[M][M];
double f[M][M][M][M][N];
double X;

int get_sum(int x1, int y1, int x2, int y2) {
    return s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1];
}

double get(int x1, int y1, int x2, int y2) {
    double sum = get_sum(x1, y1, x2, y2);
    return sum * sum;
}

double dfs(int x1, int y1, int x2, int y2, int k) {
    double &v = f[x1][y1][x2][y2][k];
    if (v >= 0) return v;
    if (k == 1) return v = get(x1, y1, x2, y2);

    v = INF;
    for (int i = x1; i < x2; i++) {
        v = min(v, get(x1, y1, i, y2) + dfs(i + 1, y1, x2, y2, k - 1));
        v = min(v, get(i + 1, y1, x2, y2) + dfs(x1, y1, i, y2, k - 1));
    }

    for (int j = y1; j < y2; j++) {
        v = min(v, get(x1, y1, x2, j) + dfs(x1, j + 1, x2, y2, k - 1));
        v = min(v, get(x1, j + 1, x2, y2) + dfs(x1, y1, x2, j, k - 1));
    }

    return v;
}

void prework() {
    cin >> n;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++) {
            cin >> s[i][j];
            s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
        }

    X = (double) s[m][m] / n;
    memset(f, -1, sizeof f);
    double ans = dfs(1, 1, 8, 8, n);
    
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= m; k++) {
                cout << f[]
            }
        }
    }
    
    cout << ans << "\n";
    ans = sqrt(ans / n - X * X);
    printf("%.3lf\n", ans);
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
        solve();
    }

    return 0;
}