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

// region 快读快写
static struct FastInput {
    template<typename T>
    inline FastInput& operator>>(T &x) {
        T ret = 0, sgn = 1;
        char c = getchar();
        while (!isdigit(c)) sgn = (c == '-' ? -1 : 1), c = getchar();
        while (isdigit(c)) ret = (ret << 3) + (ret << 1) + c - '0', c = getchar();
        x = (sgn == -1 ? -ret : ret);
        return *this;
    }
} fin;

static struct FastOutput {
    inline FastOutput& operator<<(const string& s) {
        for (int i = 0; i < (int) s.size(); i++) putchar(s[i]);
        return *this;
    }

    template <typename T>
    inline void work_int(T x) {
        static char buf[41];

        if (x == 0) {
            putchar('0');
        } else {
            int w = 0;
            if (x < 0) putchar('-'), x = -x;
            while (x) buf[++w] = (x % 10) + 48, x /= 10;
            while (w) putchar(buf[w--]);
        }
    }

    inline FastOutput& operator<<(__int128 x) {
        work_int(x);
        return *this;
    }

    template <typename T>
    inline typename enable_if<is_integral<T>::value, FastOutput&>::type operator<<(T x) {
        work_int(x);
        return *this;
    }
} fout;
// endregion

// region 最大值线段树分裂
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    const ll MOD = 1e9 + 7;

    struct Node {
        int lson, rson;
        pll sum;
    };

    int lb, rb;
    Node tr[SZ * 70];
    int nw;
    int root[SZ + 1], cnt;

    inline Seg() {
        lb = 1, rb = SZ;
    }

    inline void init(int L = 1, int R = SZ, int _cnt = 0) {
        lb = L, rb = R, cnt = _cnt;
    }

    inline void merge(int &x, int y, int s, int e) {
        if (!x || !y) {
            x |= y;
            return;
        }

        if (s == e) {
            tr[x].sum.fi += tr[y].sum.fi;
        } else {
            merge(ls(x), ls(y), s, mid);
            merge(rs(x), rs(y), mid + 1, e);
            push_up(x);
        }
    }

    inline int new_node() {
        int id = ++nw;
        return id;
    }

    inline void push_up(int k) {
        tr[k].sum = max(tr[ls(k)].sum, tr[rs(k)].sum);
    }

    inline void update(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum.fi += val;
            tr[k].sum.se = -id;
            return;
        }

        if (id <= mid) update(ls(k), s, mid, id, val);
        if (id >= mid + 1) update(rs(k), mid + 1, e, id, val);
        push_up(k);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = tr[k].mx = val;
            return;
        }

        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        push_up(k);
    }

    inline pll query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k].sum;

        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        return max(query(ls(k), s, mid, L, R), query(rs(k), mid + 1, e, L, R));
    }

    inline void merge(int &x, int y) {
        merge(x, y, lb, rb);
    }

    inline void update(int &k, int id, ll val) {
        update(k, lb, rb, id, val);
    }

    inline void set(int k, int id, ll val) {
        set(k, lb, rb, id, val);
    }

    inline pll query(int k, int L, int R) {
        if (R < L) return {0, 0};
        return query(k, lb, rb, L, R);
    }
};
// endregion

const int N = 1e5 + 10;

int n, m;
int h[N], ne[N * 2], ver[N * 2], tt;

Seg<N> seg;
int fa[22][N], dep[N];
int ans[N];

void add(int u, int v) {
    ver[++tt] = v, ne[tt] = h[u], h[u] = tt;
}

void dfs_lca(int u, int fno) {
    fa[0][u] = fno, dep[u] = dep[fno] + 1;

    for (int i = 1; i <= 20; i++) {
        int pv = fa[i - 1][u];
        fa[i][u] = fa[i - 1][pv];
    }

    for (int i = h[u]; i; i = ne[i]) {
        int v = ver[i];
        if (v == fno) continue;
        dfs_lca(v, u);
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);

    int delta = dep[x] - dep[y];
    for (int i = 0; delta; i++, delta >>= 1) {
        if (delta & 1) x = fa[i][x];
    }
    if (x == y) return x;

    for (int i = 20; i >= 0; i--) {
        if (fa[i][x] != fa[i][y]) {
            x = fa[i][x], y = fa[i][y];
        }
    }
    return fa[0][x];
}

void dfs(int u) {
    for (int i = h[u]; i; i = ne[i]) {
        int v = ver[i];
        if (v == fa[0][u]) continue;
        dfs(v);
        seg.merge(seg.root[u], seg.root[v]);
    }

    auto[c, id] = seg.query(seg.root[u], 1, N);
    if (c > 0) ans[u] = -id;
}

void solve() {
    dfs_lca(1, 0);
    seg.init(1, N);

    for (int i = 1; i <= m; i++) {
        int x, y, z;
        fin >> x >> y >> z;
        int lca1 = lca(x, y), lca2 = fa[0][lca1];
        seg.update(seg.root[x], z, 1);
        seg.update(seg.root[y], z, 1);
        seg.update(seg.root[lca1], z, -1);
        seg.update(seg.root[lca2], z, -1);
    }

    dfs(1);
    for (int i = 1; i <= n; i++) fout << ans[i] << "\n";
}

void prework() {
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    prework();
//    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
//    cin >> T;
    while (T--) {
        fin >> n >> m;
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            fin >> u >> v;
            add(u, v), add(v, u);
        }
        solve();
    }

    return 0;
}