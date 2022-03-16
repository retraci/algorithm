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

// region 主席树
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        ll sum;
    };

    int lb, rb, mem;
    Node tr[32 * SZ];
    int root[SZ + 1];

    inline Seg() {
        init(1, SZ);
    }

    inline void init(int L, int R) {
        mem = 0, lb = L, rb = R;
        tr[0].lson = tr[0].rson = 0;
        tr[0].sum = 1e18;
    }

    inline int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        tr[id].sum = 1e18;
        return id;
    }

    inline void push_up(int k) {
        tr[k].sum = min(tr[ls(k)].sum, tr[rs(k)].sum);
    }

    inline void build(ll a[]) {
        root[0] = build(lb, rb, a);
    }

    inline int build(int s, int e, ll a[]) {
        int k = new_node();

        if (s == e) {
            tr[k].sum = a[s];
            return k;
        }

        ls(k) = build(s, mid, a);
        rs(k) = build(mid + 1, e, a);
        push_up(k);
        return k;
    }

    inline int update(int p, int s, int e, int id, ll val) {
        int k = new_node();
        tr[k] = tr[p];

        if (s == e) {
            tr[k].sum = min(tr[k].sum, val);
            return k;
        }

        if (id <= mid) ls(k) = update(ls(p), s, mid, id, val);
        if (id >= mid + 1) rs(k) = update(rs(p), mid + 1, e, id, val);
        push_up(k);
        return k;
    }

    inline int set(int p, int s, int e, int id, ll val) {
        int k = new_node();
        if (p) tr[k] = tr[p];

        if (s == e) {
            tr[k].sum = val;
            return k;
        }

        if (id <= mid) ls(k) = set(ls(p), s, mid, id, val);
        if (id >= mid + 1) rs(k) = set(rs(p), mid + 1, e, id, val);
        push_up(k);
        return k;
    }

    inline ll query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k].sum;

        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        return min(query(ls(k), s, mid, L, R), query(rs(k), mid + 1, e, L, R));
    }

    inline ll query_kth(int k, int p, int s, int e, ll x) {
        if (s == e) return s;
        ll cnt = tr[ls(k)].sum - tr[ls(p)].sum;

        if (x <= cnt) return query_kth(ls(k), ls(p), s, mid, x);
        else return query_kth(rs(k), rs(p), mid + 1, e, x - cnt);
    }

    inline ll query_lim(int k, int p, int s, int e, ll lim) {
        if (s == e) {
            ll cnt = tr[k].sum - tr[p].sum;
            if (cnt >= lim) return e;
            return 1e9;
        }

        ll res = 1e9;
        ll lc = tr[ls(k)].sum - tr[ls(p)].sum;
        ll rc = tr[rs(k)].sum - tr[rs(p)].sum;
        if (lc >= lim) res = min(res, query_lim(ls(k), ls(p), s, mid, lim));
        if (rc >= lim) res = min(res, query_lim(rs(k), rs(p), mid + 1, e, lim));
        return res;
    }

    inline void update(int nv, int pv, int id, ll val) {
        root[nv] = update(root[pv], lb, rb, id, val);
    }

    inline void set(int nv, int pv, int id, ll val) {
        root[nv] = set(root[pv], lb, rb, id, val);
    }

    inline ll query(int v, int L, int R) {
        if (R < L) return 1e18;
        return query(root[v], lb, rb, L, R);
    }

    inline ll query_kth(int L, int R, ll x) {
        return query_kth(root[R], root[L - 1], lb, rb, x);
    }

    inline ll query_lim(int L, int R, ll lim) {
        return query_lim(root[R], root[L - 1], lb, rb, lim);
    }
};
// endregion

const int N = 100010;

int n, Q;
int a[N];

int g[2 * N], ne[2 * N], h[N], edm;
int rt;
int dep[N], in[N], out[N], cnt;

Seg<N> seg;

void add(int u, int v) {
    g[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void dfs(int u, int fno) {
    in[u] = ++cnt;
    for (int i = h[u]; ~i; i = ne[i]) {
        int v = g[i];
        if (v == fno) continue;

        dep[v] = dep[u] + 1;
        dfs(v, u);
    }
    out[u] = cnt;
}

void solve() {
    dep[rt] = 1;
    dfs(rt, -1);
    int mx_dep = *max_element(dep + 1, dep + n + 1);
    vector<int> ds[mx_dep + 1];
    for (int i = 1; i <= n; i++) {
        ds[dep[i]].push_back(i);
    }

    seg.init(1, cnt);
    for (int i = 1; i <= mx_dep; i++) {
        seg.root[i] = seg.root[i - 1];
        for (int x : ds[i]) {
            seg.update(i, i, in[x], a[x]);
        }
    }

    int lst = 0, oh = 0;
    cin >> Q;
    while (Q--) {
        int x, y;
        cin >> x >> y;

        int u = (x + lst) % n + 1, k = (y + lst) % n;
        int d = min(mx_dep, dep[u] + k);
        lst = seg.query(d, in[u], out[u]);
        cout << lst << "\n";
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
        cin >> n >> rt;
        fill(h, h + n + 1, -1), edm = 0;

        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            add(u, v), add(v, u);
        }

        solve();
    }

    return 0;
}