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
    // 上, 右, 下, 左  |  左上, 右上, 右下, 左下
    const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 3e5 + 10;

// region 区间开关, 维护最值线段树
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        ll lz, mx, mi;
        ll mx_bak, mi_bak;
    };

    int lb, rb, rt, mem;
    Node tr[SZ * 4];

    inline Seg() {
        init(1, SZ);
    }

    inline void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        tr[0].lson = tr[0].rson = 0;
        tr[0].lz = tr[0].mx = tr[0].mx_bak = 0;
        tr[0].mi = tr[0].mi_bak = 1e9;
    }

    inline void init(int L, int R, ll val) {
        init(L, R);
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        tr[id].lz = tr[id].mx = tr[id].mx_bak = 0;
        tr[id].mi = tr[id].mi_bak = 1e9;
        return id;
    }

    inline void push_up(Node &fa, Node &lc, Node &rc) {
        fa.mx = max(lc.mx, rc.mx);
        fa.mx_bak = max(lc.mx_bak, rc.mx_bak);
        fa.mi = min(lc.mi, rc.mi);
        fa.mi_bak = min(lc.mi_bak, rc.mi_bak);
    }

    inline void push_up(int k) {
        push_up(tr[k], tr[ls(k)], tr[rs(k)]);
    }

    inline void work(Node &t, ll col) {
        t.lz = col;
        if (col == 1) {
            t.mx = t.mx_bak;
            t.mi = t.mi_bak;
        } else {
            t.mx = 0, t.mi = 1e9;
        }
    }

    inline void push_down(int k, int s, int e) {
        if (tr[k].lz) {
            if (!ls(k)) ls(k) = new_node();
            if (!rs(k)) rs(k) = new_node();
            work(tr[ls(k)], tr[k].lz);
            work(tr[rs(k)], tr[k].lz);
            tr[k].lz = 0;
        }
    }

    inline void add(int &k, int s, int e, int L, int R, ll col) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            work(tr[k], col);
            return;
        }

        push_down(k, s, e);
        if (L <= mid) add(ls(k), s, mid, L, R, col);
        if (R >= mid + 1) add(rs(k), mid + 1, e, L, R, col);
        push_up(k);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].mi_bak = tr[k].mx_bak = val;
            return;
        }

        push_down(k, s, e);
        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        push_up(k);
    }

    inline Node query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k];

        push_down(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        Node res = {0, 0, 0, 0, (ll) 1e9, 0};
        Node lc = query(ls(k), s, mid, L, R);
        Node rc = query(rs(k), mid + 1, e, L, R);
        push_up(res, lc, rc);
        return res;
    }

    inline void add(int L, int R, ll val) {
        if (R < L) return;
        add(rt, lb, rb, L, R, val);
    }

    inline void set(int id, ll val) {
        set(rt, lb, rb, id, val);
    }

    inline Node query(int L, int R) {
        if (R < L) return {0, 0, 0, 0, (ll) 1e9, 0};
        return query(rt, lb, rb, L, R);
    }
};
// endregion

// region kruskal重构树
int n, m;
ti3 es[N];

int h[2 * N], ne[2 * N], g[2 * N], edm;
int pa[2 * N], w[2 * N], tt;

int id[2 * N], eula[4 * N], dep[4 * N], cnt;
int st[4 * N][23], lg[4 * N];

int find(int x) {
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}

bool unite(int x, int y) {
    int tx = find(x), ty = find(y);
    if (tx == ty) return false;
    pa[tx] = ty;
    return true;
}

void add(int u, int v) {
    g[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void dfs(int u) {
    eula[++cnt] = u, id[u] = cnt;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = g[i];

        dep[v] = dep[u] + 1;
        dfs(v);
        eula[++cnt] = u;
    }
}

void init_st(int rt) {
    dep[rt] = 1;
    dfs(tt);

    lg[0] = -1;
    for (int i = 1; i <= cnt; i++) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= cnt; i++) st[i][0] = eula[i];
    for (int k = 1; (1 << k) <= cnt; k++) {
        for (int i = 1; i + (1 << k) - 1 <= cnt; i++) {
            int a = st[i][k - 1];
            int b = st[i + (1 << (k - 1))][k - 1];

            st[i][k] = dep[a] < dep[b] ? a : b;
        }
    }
}

int lca(int x, int y) {
    int L = id[x], R = id[y];
    if (L > R) swap(L, R);

    int k = lg[R - L + 1];
    int a = st[L][k];
    int b = st[R - (1 << k) + 1][k];

    return dep[a] < dep[b] ? a : b;
}

void kruskal_init() {
    sort(es + 1, es + n - 1 + 1, [](auto &a, auto &b) {
        return get<2>(a) < get<2>(b);
    });

    iota(pa, pa + 2 * n + 1, 0);
    fill(h, h + 2 * n + 1, -1), edm = 0;
    tt = n;
    for (int i = 1; i <= n - 1; i++) {
        auto [u, v, cost] = es[i];
        int tu = find(u), tv = find(v);
        if (tu == tv) continue;

        tt++;
        unite(tu, tt), unite(tv, tt);
        add(tt, tu), add(tt, tv);
        w[tt] = cost;
    }

    init_st(tt);
}
// endregion

Seg<N> seg;

void solve() {
    kruskal_init();

    seg.init(1, n);
    for (int i = 1; i <= n; i++) seg.set(i, id[i]);

    while (m--) {
        int op;
        cin >> op;
        if (op != 3) {
            int L, R;
            cin >> L >> R;

            seg.add(L, R, op);
        } else {
            int x;
            cin >> x;

            auto t = seg.query(1, n);
            int mi = min(id[x], (int) t.mi), mx = max(id[x], (int) t.mx);
            int ans = w[lca(eula[mi], eula[mx])];

            cout << (ans == 0 ? -1 : ans) << "\n";
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
        for (int i = 1; i <= n - 1; i++) {
            int u, v, cost;
            cin >> u >> v >> cost;
            es[i] = {u, v, cost};
        }
        solve();
    }

    return 0;
}