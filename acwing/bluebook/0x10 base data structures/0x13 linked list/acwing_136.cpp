#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#include <map>
#include <array>

using namespace std;

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
typedef std::array<int, 2> ai2;
typedef std::array<ll, 2> al2;
typedef std::array<int, 3> ai3;
typedef std::array<ll, 3> al3;
typedef std::array<int, 4> ai4;
typedef std::array<ll, 4> al4;
// endregion
// region grid_delta
namespace grid_delta {
    // 上, 右, 下, 左  |  左上, 右上, 左下, 右下
    const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
    const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};
}
// endregion

const int N = 1e5 + 10;

int n;
int va[N];

void solve() {
    set<pii> ts;
    ts.insert({va[1], 1});
    for (int i = 2; i <= n; i++) {
        auto it = ts.lower_bound({va[i], i});
        auto ret = it;
        int tmp = 0x3f3f3f3f;
        if (it != ts.end()) {
            if (abs((*it).fi - va[i]) < tmp) {
                ret = it;
                tmp = abs((*it).fi - va[i]);
            }
        }
        while (it != ts.begin()) {
            --it;
            if (abs((*it).fi - va[i]) <= tmp) {
                ret = it;
                tmp = abs((*it).fi - va[i]);
            } else {
                break;
            }
        }

        cout << tmp << " " << (*ret).se << endl;

        ts.insert({va[i], i});
    }
}

int main() {
//    freopen("../in.txt", "r", stdin);

    cin >> n;
    for (int i = 1; i <= n; i++) scanf("%d", &va[i]);
    solve();

    return 0;
}