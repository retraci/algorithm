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

const int N = 110;
const int M = 1 << 10;

int n, m;
int g[N];

vector<int> state;
int cnt[M];
vector<int> nex[M];

bool check(int mask) {
    for (int i = 0; i < m; i++) {
        if (mask >> i & 1 && (mask >> (i + 1) & 1 || mask >> (i + 2) & 1)) return false;
    }
    return true;
}

void init() {
    int lim = 1 << m;
    for (int mask = 0; mask < lim; mask++) {
        if (check(mask)) {
            state.push_back(mask);
            cnt[mask] = __builtin_popcount(mask);
        }
    }

    for (int a = 0; a < state.size(); a++) {
        for (int b = 0; b < state.size(); b++) {
            int sa = state[a], sb = state[b];
            if (sa & sb) continue;
            nex[a].push_back(b);
        }
    }
}

void solve() {
    init();

    int ns = state.size();
    int f[2][ns][ns];
    memset(f, 0, sizeof f);
    f[0][0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int a = 0; a < state.size(); a++) {
            for (int b : nex[a]) {
                for (int c : nex[b]) {
                    int sa = state[a], sc = state[c];
                    if (sa & sc || sc & g[i + 1]) continue;
                    f[i + 1 & 1][b][c] = max(f[i + 1 & 1][b][c], f[i & 1][a][b] + cnt[sc]);
                }
            }
        }
    }

    cout << *max_element(&f[n & 1][0][0], &f[n & 1][ns - 1][ns]) << "\n";
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
        for (int i = 1; i <= n; i++) {
            string str;
            cin >> str;
            int stat = 0;
            for (int j = 0; j < m; j++) {
                stat |= (str[j] == 'H') << j;
            }
            g[i] = stat;
        }
        solve();
    }

    return 0;
}