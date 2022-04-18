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

// region 区修线段树
template<class Info, class Tag, int SZ,
        class Merge = std::plus<Info>>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)

    const Merge merge;
    int lb, rb, rt, mem;
    Info info[SZ * 4];
    Tag tag[SZ * 4];

    Seg() : merge(Merge()) {
        init(1, SZ);
    }

    void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        info[0] = Info();
        tag[0] = Tag();
    }

    int new_node() {
        int id = ++mem;
        info[id] = Info();
        tag[id] = Tag();
        return id;
    }

    void pull(int k) {
        info[k].set(merge(info[ls(k)], info[rs(k)]));
    }

    void apply(int k, ll sz, const Tag &v) {
        info[k].apply(sz, v);
        tag[k].apply(v);
    }

    void push(int k, int s, int e) {
        if (tag[k].check()) {
            ll len = e - s + 1;
            ll lsz = len - len / 2, rsz = len / 2;
            if (!ls(k)) ls(k) = new_node();
            if (!rs(k)) rs(k) = new_node();
            apply(ls(k), lsz, tag[k]);
            apply(rs(k), rsz, tag[k]);
            tag[k] = Tag();
        }
    }

    void upd(int &k, int s, int e, int L, int R, const Tag &v) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            apply(k, e - s + 1, v);
            return;
        }

        push(k, s, e);
        if (L <= mid) upd(ls(k), s, mid, L, R, v);
        if (R >= mid + 1) upd(rs(k), mid + 1, e, L, R, v);
        pull(k);
    }

    void set(int &k, int s, int e, int id, const Info &v) {
        if (!k) k = new_node();

        if (s == e) {
            info[k].set(v);
            return;
        }

        push(k, s, e);
        if (id <= mid) set(ls(k), s, mid, id, v);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, v);
        pull(k);
    }

    Info qr(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return info[k];

        push(k, s, e);
        if (R <= mid) return qr(ls(k), s, mid, L, R);
        if (L >= mid + 1) return qr(rs(k), mid + 1, e, L, R);
        return merge(qr(ls(k), s, mid, L, R), qr(rs(k), mid + 1, e, L, R));
    }

    int qr_kth(int k, int s, int e, ll x) {
        if (s == e) return s;

        if (x <= info[ls(k)].sum) return qr_kth(ls(k), s, mid, x);
        else return qr_kth(rs(k), mid + 1, e, x - info[ls(k)].sum);
    }

    void upd(int L, int R, const Tag &v) {
        if (R < L) return;
        upd(rt, lb, rb, L, R, v);
    }

    void set(int id, const Info &v) {
        set(rt, lb, rb, id, v);
    }

    Info qr(int L, int R) {
        if (R < L) return Info();
        return qr(rt, lb, rb, L, R);
    }

    int qr_kth(ll x) {
        return qr_kth(rt, lb, rb, x);
    }
};
// endregion

// region 区修, 维护最值, 1: 开, 0: 关
struct Tag {
    ll x;
    Tag(ll x = -1) : x(x) {}

    bool check() const {
        return x != -1;
    }

    void apply(const Tag &a) {
        if (!a.check()) return;
        x = a.x;
    }
};

struct Info {
    int lson, rson;
    ll mi, mx, mi_bak, mx_bak;
    Info(ll mi = 1e9, ll mx = 0, ll mi_bak = 1e9, ll mx_bak = 0) : lson(0), rson(0), mi(mi), mx(mx), mi_bak(mi_bak), mx_bak(mx_bak) {}

    void apply(ll sz, const Tag &a) {
        if (!a.check()) return;
        if (a.x) {
            mi = mi_bak, mx = mx_bak;
        } else {
            mi = 1e9, mx = 0;
        }
    }

    friend Info operator+(const Info &a, const Info &b) {
        return {min(a.mi, b.mi), max(a.mx, b.mx), min(a.mi_bak, b.mi_bak), max(a.mx_bak, b.mx_bak)};
    }

    void set(const Info &a) {
        mi = a.mi, mx = a.mx;
        mi_bak = a.mi_bak, mx_bak = a.mx_bak;
    }
};
// endregion

// region kruskal重构树
int n, m;
ti3 es[N];

int h[2 * N], ne[2 * N], g[2 * N], edm;
int pa[2 * N], w[2 * N], tt;

int id[2 * N], eula[4 * N], dep[4 * N], cnt;
int st[4 * N][23];

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

    int k = __lg(R - L + 1);
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

Seg<Info, Tag, N> seg;

void solve() {
    kruskal_init();

    seg.init(1, n);
    for (int i = 1; i <= n; i++) seg.set(i, {(ll) 1e9, 0, id[i], id[i]});

    while (m--) {
        int op;
        cin >> op;
        if (op != 3) {
            int L, R;
            cin >> L >> R;

            seg.upd(L, R, op == 1);
        } else {
            int x;
            cin >> x;

            auto t = seg.qr(1, n);
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