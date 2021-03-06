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
    // ???, ???, ???, ???  |  ??????, ??????, ??????, ??????
    const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
    const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 55;

int n;
int va[N];

int up[N], down[N];
int ans;

void dfs(int cur, int su, int sd) {
    if (su + sd >= ans) return;
    if (cur > n) {
        ans = min(ans, su + sd);
        return;
    }

    // ??????????????????
    {
        int tmp = 0, id = 0;
        for (int i = 1; i <= su; i++) {
            if (up[i] >= va[cur]) continue;

            if (up[i] > tmp) {
                tmp = up[i], id = i;
            }
        }

        if (id != 0) {
            up[id] = va[cur];
            dfs(cur + 1, su, sd);
            up[id] = tmp;
        } else {
            // ???????????????????????????
            up[su + 1] = va[cur];
            dfs(cur + 1, su + 1, sd);
        }
    }

    // ??????????????????
    {
        int tmp = 1e9, id = 0;
        for (int i = 1; i <= sd; i++) {
            if (down[i] <= va[cur]) continue;

            if (down[i] < tmp) {
                tmp = down[i], id = i;
            }
        }

        if (id != 0) {
            down[id] = va[cur];
            dfs(cur + 1, su, sd);
            down[id] = tmp;
        } else {
            // ???????????????????????????
            down[sd + 1] = va[cur];
            dfs(cur + 1, su, sd + 1);
        }
    }
}

void solve() {
    ans = 1e9;
    dfs(1, 0, 0);
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
    while (cin >> n, n) {
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}