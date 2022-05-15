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
#include <cassert>
#include <random>
#include <cmath>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;
using ai3 = array<int, 3>;

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;
const int M = 2 * N;

// region 区间修改fenwick
template<int SZ>
struct Fenwick {
    int n;
    ll tr1[SZ + 10], tr2[SZ + 10];

    Fenwick() {}

    void init(int _n, ll v = 0) {
        n = _n;
        fill(tr1, tr1 + n + 1, v);
        fill(tr2, tr2 + n + 1, v);
    }

    void add(ll tr[], int id, ll x) {
        for (int i = id; i <= n; i += i & -i) tr[i] += x;
    }

    ll query(ll tr[], int id) {
        ll res = 0;
        for (int i = id; i; i -= i & -i) res += tr[i];
        return res;
    }

    ll get(int id) {
        return (id + 1) * query(tr1, id) - query(tr2, id);
    }

    void upd(int L, int R, ll x) {
        add(tr1, L, x), add(tr1, R + 1, -x);
        add(tr2, L, x * L), add(tr2, R + 1, -x * (R + 1));
    }

    ll qr(int L, int R) {
        return get(R) - get(L - 1);
    }
};
// endregion

int n, m;
int a[N];
int h[N], ne[M * 2], e[M * 2], edm;
int dep[N], sz[N], fa[N], son[N], top[N], id[N], cnt;
Fenwick<N> fw;

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void dfs1(int u, int fno, int depth) {
    fa[u] = fno, dep[u] = depth, sz[u] = 1;

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fno) continue;

        dfs1(v, u, depth + 1);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

void dfs2(int u, int fno, int tp) {
    id[u] = ++cnt, top[u] = tp;

    if (!son[u]) return;
    dfs2(son[u], u, tp);

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fno || v == son[u]) continue;

        dfs2(v, u, v);
    }
}

void upd_path(int u, int v, int k) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        int nu = top[u], nv = top[v];

        int L = id[nu], R = id[u];
        fw.upd(L, R, k);

        u = fa[nu];
    }

    if (dep[u] < dep[v]) swap(u, v);
    fw.upd(id[v], id[u], k);
}

void upd_tree(int u, int k) {
    int L = id[u], R = id[u] + sz[u] - 1;
    fw.upd(L, R, k);
}

ll qr_path(int u, int v) {
    ll res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        int nu = top[u], nv = top[v];

        int L = id[nu], R = id[u];
        res += fw.qr(L, R);

        u = fa[nu];
    }

    if (dep[u] < dep[v]) swap(u, v);
    res += fw.qr(id[v], id[u]);

    return res;
}

ll qr_tree(int u) {
    int L = id[u], R = id[u] + sz[u] - 1;
    return fw.qr(L, R);
}

void solve() {
    dfs1(1, -1, 1);
    dfs2(1, -1, 1);

    fw.init(n);
    for (int i = 1; i <= n; i++) fw.upd(id[i], id[i], a[i]);

    cin >> m;
    while (m--) {
        int op;
        cin >> op;

        if (op == 1) {
            int u, v, k;
            cin >> u >> v >> k;

            upd_path(u, v, k);
        }
        if (op == 2) {
            int u, k;
            cin >> u >> k;

            upd_tree(u, k);
        }
        if (op == 3) {
            int u, v;
            cin >> u >> v;

            cout << qr_path(u, v) << "\n";
        }
        if (op == 4) {
            int u;
            cin >> u;

            cout << qr_tree(u) << "\n";
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
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n;
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