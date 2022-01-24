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

// region 普通线段树分裂
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    const ll MOD = 1e9 + 7;

    struct Node {
        int lson, rson;
        ll sum;
    };

    int lb, rb;
    Node tr[SZ * 40];
    int gc[SZ * 40], ct;
    int cn;
    int root[SZ + 1], cnt;

    inline Seg() {
        lb = 1, rb = SZ;
    }

    inline void init(int L = 1, int R = SZ, int _cnt = 0) {
        lb = L, rb = R, cnt = _cnt;
    }

    inline void merge(int &x, int y) {
        if (!x || !y) {
            x |= y;
            return;
        }

        tr[x].sum += tr[y].sum;
        merge(ls(x), ls(y));
        merge(rs(x), rs(y));
        del_node(y);
    }

    inline void split(int x, int &y, int k, int op) {
        if (tr[x].sum == k) return;

        y = new_node();
        if (!op) {
            if (k <= tr[rs(x)].sum) {
                split(rs(x), rs(y), k, op);
                ls(y) = ls(x), ls(x) = 0;
            } else {
                split(ls(x), ls(y), k - tr[rs(x)].sum, op);
            }
        } else {
            if (k <= tr[ls(x)].sum) {
                split(ls(x), ls(y), k, op);
                rs(y) = rs(x), rs(x) = 0;
            } else {
                split(rs(x), rs(y), k - tr[ls(x)].sum, op);
            }
        }
        push_up(x), push_up(y);
    }

    inline int new_node() {
        return ct ? gc[ct--] : ++cn;
    }

    inline void del_node(int x) {
        gc[++ct] = x;
        tr[x] = {0, 0, 0};
    }

    inline void push_up(int k) {
        tr[k].sum = tr[ls(k)].sum + tr[rs(k)].sum;
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = val;
            return;
        }

        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        push_up(k);
    }

    inline ll query(int k, int s, int e, int x) {
        if (s == e) return s;

        if (x <= tr[ls(k)].sum) return query(ls(k), s, mid, x);
        else return query(rs(k), mid + 1, e, x - tr[ls(k)].sum);
    }

    inline void set(int &k, int id, ll val) {
        set(k, lb, rb, id, val);
    }
};
// endregion

const int N = 1e5 + 10;

int n, m;
int va[N];
int ops[N];

Seg<N> seg;
set<int> st;

set<int>::iterator work(int x) {
    auto it = st.lower_bound(x);
    if (*it == x) return it;
    it--;
    seg.split(seg.root[*it], seg.root[x], x - *it, ops[x] = ops[*it]);
    return st.insert(x).fi;
}

void solve() {
    seg.init(1, n);
    st.insert(n + 1);
    for (int i = 1; i <= n; i++) {
        seg.set(seg.root[i], i, 1);
        st.insert(i);
    }

    while (m--) {
        int op, id;
        cin >> op >> id;
        int L, R;
        if (op) L = id, R = n;
        else L = 1, R = id;

        auto it1 = work(L), it2 = work(R + 1);
        it1++;
        for (auto it = it1; it != it2; it++) {
            seg.merge(seg.root[L], seg.root[*it]);
        }
        ops[L] = op;
        st.erase(it1, it2);
    }

    for (int i = 1; i <= n; i++) {
        work(i), work(i + 1);
        cout << seg.query(seg.root[i], 1, n, 1) << " ";
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
//    cin >> T;
    while (T--) {
        cin >> n >> m;
        solve();
    }

    return 0;
}