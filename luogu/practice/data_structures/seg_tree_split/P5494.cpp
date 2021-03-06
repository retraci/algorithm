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

// region ?????????????????????
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    const ll MOD = 1e9 + 7;

    struct Node {
        int lson, rson;
        ll sum, lz;
    };

    int lb, rb;
    Node tr[SZ * 40];
    int nw;
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
        tr[x].lz += tr[y].lz;
        merge(ls(x), ls(y));
        merge(rs(x), rs(y));
    }

    inline int split(int &k, int s, int e, int L, int R) {
        int id = new_node();
        if (L <= s && R >= e) {
            tr[id] = tr[k];
            k = 0;
        } else {
            if (L <= mid) tr[id].lson = split(ls(k), s, mid, L, R);
            if (R >= mid + 1) tr[id].rson = split(rs(k), mid + 1, e, L, R);
            push_up(k), push_up(id);
        }
        return id;
    }

    inline int new_node() {
        int id = ++nw;
        tr[id].sum = tr[id].lz = 0;
        return id;
    }

    inline void push_up(int k) {
        tr[k].sum = tr[ls(k)].sum + tr[rs(k)].sum;
    }

    inline void push_down(int k, int s, int e) {
        if (!ls(k)) ls(k) = new_node();
        if (!rs(k)) rs(k) = new_node();
        ll len = e - s + 1;
        ll lsz = len - len / 2, rsz = len / 2;
        if (tr[k].lz) {
            tr[ls(k)].sum = tr[ls(k)].sum + lsz * tr[k].lz;
            tr[rs(k)].sum = tr[rs(k)].sum + rsz * tr[k].lz;
            tr[ls(k)].lz = tr[ls(k)].lz + tr[k].lz;
            tr[rs(k)].lz = tr[rs(k)].lz + tr[k].lz;
            tr[k].lz = 0;
        }
    }

    inline void update(int &k, int s, int e, int L, int R, ll val) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            tr[k].sum = tr[k].sum + (e - s + 1) * val;
            tr[k].lz = tr[k].lz + val;
            return;
        }

//        push_down(k, s, e);
        if (L <= mid) update(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) update(rs(k), mid + 1, e, L, R, val);
        push_up(k);
    }

    inline ll query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k].sum;

//        push_down(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        return query(ls(k), s, mid, L, R) + query(rs(k), mid + 1, e, L, R);
    }

    inline ll query(int k, int s, int e, int x) {
        if (s == e) return s;
        if (x <= tr[ls(k)].sum) return query(ls(k), s, mid, x);
        else return query(rs(k), mid + 1, e, x - tr[ls(k)].sum);
    }

    inline int split(int &k, int L, int R) {
        return split(k, lb, rb, L, R);
    }

    inline void update(int &k, int L, int R, ll val) {
        update(k, lb, rb, L, R, val);
    }

    inline ll query(int k, int L, int R) {
        return query(k, lb, rb, L, R);
    }

    inline ll query(int k, int x) {
        return query(k, lb, rb, x);
    }
};
// endregion

const int N = 2e5 + 10;

int n, m;
int va[N];

Seg<N> seg;

void solve() {
    seg.init(1, n, 1);
    for (int i = 1; i <= n; i++) {
        seg.update(seg.root[1], i, i, va[i]);
    }

    while (m--) {
        int op, p, x, y;
        cin >> op >> p;
        if (op == 0) {
            cin >> x >> y;
            int rt = seg.root[p];
            seg.root[++seg.cnt] = seg.split(rt, x, y);
        } else if (op == 1) {
            cin >> x;
            int rt1 = seg.root[p], rt2 = seg.root[x];
            seg.merge(rt1, rt2);
        } else if (op == 2) {
            cin >> x >> y;
            int rt = seg.root[p];
            seg.update(rt, y, y, x);
        } else if (op == 3) {
            cin >> x >> y;
            int rt = seg.root[p];
            cout << seg.query(rt, x, y) << "\n";
        } else {
            cin >> x;
            int rt = seg.root[p];
            if (seg.tr[rt].sum < x) cout << -1 << "\n";
            else cout << seg.query(rt, x) << "\n";
        }
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
        for (int i = 1; i <= n; i++) cin >> va[i];
        solve();
    }

    return 0;
}