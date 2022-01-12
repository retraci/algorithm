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

const int N = 1e3 + 10;

int n, m;
string va[N];
string t;

void solve() {
    unordered_map<string, ti3> mp;
    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= m; j++) {
            int lb = j - 2 + 1, rb = j;
            mp[va[i].substr(lb, 2)] = {lb, rb, i};
        }

        for (int j = 3; j <= m; j++) {
            int lb = j - 3 + 1, rb = j;
            mp[va[i].substr(lb, 3)] = {lb, rb, i};
        }
    }

    ti3 none = {1e9, 1e9, 1e9};
    ti3 f[m + 1];
    fill(f, f + m + 1, none);
    f[0] = {0, 0, 0};
    for (int i = 2; i <= m; i++) {
        if (i - 2 >= 0 && f[i - 2] != none) {
            string sub = t.substr(i - 2 + 1, 2);
            if (mp.count(sub)) f[i] = mp[sub];
        }
        if (i - 3 >= 0 && f[i - 3] != none) {
            string sub = t.substr(i - 3 + 1, 3);
            if (mp.count(sub)) f[i] = mp[sub];
        }
    }

    if (f[m] == none) {
        cout << -1 << "\n";
        return;
    }

    vector<ti3> ans;
    int cur = m;
    while (cur > 0) {
        auto [lb, rb, id] = f[cur];
        ans.push_back(f[cur]);
        cur -= rb - lb + 1;
    }

    cout << ans.size() << "\n";
    for (int i = ans.size() - 1; i >= 0; i--) {
        auto [lb, rb, id] = ans[i];
        cout << lb << " " << rb << " " << id << "\n";
    }
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
        for (int i = 1; i <= n; i++) {
            cin >> va[i];
            va[i] = ' ' + va[i];
        }
        cin >> t;
        t = ' ' + t;
        solve();
    }

    return 0;
}