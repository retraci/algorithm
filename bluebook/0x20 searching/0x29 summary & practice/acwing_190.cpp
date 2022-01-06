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

const int N = 11;

int n;
string s, t;
string va[N], vb[N];

int work(queue<string> &que, unordered_map<string, int> &d1, unordered_map<string, int> &d2, string *vu, string *vv) {
    int sz = que.size();
    while (sz--) {
        string cur = que.front(); que.pop();

        for (int i = 0; i < n; i++) {
            int pos = 0;
            while (1) {
                int id = cur.find(vu[i], pos);
                if (id == -1) break;

                string ns = cur.substr(0, id) + vv[i] + cur.substr(id + vu[i].size());
                if (!d1.count(ns)) {
                    d1[ns] = d1[cur] + 1;
                    que.push(ns);
                    if (d2.count(ns)) return d1[ns] + d2[ns];
                }

                pos = id + vu[i].size();
            }
        }
    }

    return 11;
}

int bfs() {
    if (s == t) return 0;

    queue<string> q1, q2;
    unordered_map<string, int> d1, d2;
    d1[s] = 0, d2[t] = 0;
    q1.push(s), q2.push(t);
    int step = 0;
    while (!q1.empty() && !q2.empty()) {
        int ret;
        if (q1.size() < q2.size()) ret = work(q1, d1, d2, va, vb);
        else ret = work(q2, d2, d1, vb, va);

        if (ret <= 10) return ret;
        if (++step > 10) return -1;
    }

    return -1;
}

void solve() {
    int ans = bfs();
    if (ans == -1) cout << "NO ANSWER!" << "\n";
    else cout << ans << "\n";
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
    while (T--) {
        cin >> s >> t;
        while (cin >> va[n] >> vb[n]) n++;
        solve();
    }

    return 0;
}