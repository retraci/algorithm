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

// region 区修线段树
template<class Info, class Tag, int SZ,
        class Plus = std::plus<Info>>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)

    const Plus plus;
    int lb, rb, rt, mem;
    Info info[SZ * 4];
    Tag tag[SZ * 4];

    Seg() : plus(Plus()) {}

    void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        info[0] = Info();
        tag[0] = Tag();
    }

    int new_node() {
        int id = ++mem;
        assert(id < SZ * 4);
        info[id] = Info();
        tag[id] = Tag();
        return id;
    }

    void pull(int k) {
        info[k].set(plus(info[ls(k)], info[rs(k)]));
    }

    void apply(int k, int s, int e, const Tag &v) {
        info[k].apply(s, e, v);
        tag[k].apply(s, e, v);
    }

    void push(int k, int s, int e) {
        if (tag[k].check()) {
            if (!ls(k)) ls(k) = new_node();
            if (!rs(k)) rs(k) = new_node();
            apply(ls(k), s, mid, tag[k]);
            apply(rs(k), mid + 1, e, tag[k]);
            tag[k] = Tag();
        }
    }

    void upd(int &k, int s, int e, int L, int R, const Tag &v) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            apply(k, s, e, v);
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
        return plus(qr(ls(k), s, mid, L, R), qr(rs(k), mid + 1, e, L, R));
    }

    int kth(int k, int s, int e, ll x) {
        if (s == e) return x <= info[k].sum ? s : rb + 1;

        push(k, s, e);
        if (x <= info[ls(k)].sum) return kth(ls(k), s, mid, x);
        else return kth(rs(k), mid + 1, e, x - info[ls(k)].sum);
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

    int kth(ll x) {
        return kth(rt, lb, rb, x);
    }
};
// endregion

// region 区间求和
struct Tag {
    ll x;

    Tag(ll x = -1) : x(x) {}

    bool check() const {
        return x != -1;
    }

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        x = a.x;
    }
};

struct Info {
    int lson, rson;
    ll sum;

    Info(ll sum = 0) : lson(0), rson(0), sum(sum) {}

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        sum = (e - s + 1) * a.x;
    }

    friend Info operator+(const Info &a, const Info &b) {
        return a.sum + b.sum;
    }

    void set(const Info &a) {
        sum = a.sum;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 100010;
const int M = 100010;

int n, m;
int a[N];
int h[N], ne[M * 2], e[M * 2], edm;
int dep[N], fa[N], sz[N], son[N], id[N], top[N], cnt;
Seg<Info, Tag, N> seg;

void add(int u, int v) {
    e[edm] = v, ne[edm] = h[u], h[u] = edm++;
}

void dfs1(int u, int fno, int depth) {
    dep[u] = depth, fa[u] = fno, sz[u] = 1;

    for (int i = h[u]; ~i; i = ne[i]) {
        int v = e[i];
        if (v == fno) continue;

        dfs1(v, u, depth + 1);
        sz[u] += sz[v];
        if (sz[son[u]] < sz[v]) son[u] = v;
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

        int nu = top[u];
        int L = id[nu], R = id[u];
        seg.upd(L, R, k);

        u = fa[nu];
    }

    if (dep[u] < dep[v]) swap(u, v);
    seg.upd(id[v], id[u], k);
}

void upd_tree(int u, int k) {
    int L = id[u], R = id[u] + sz[u] - 1;
    seg.upd(L, R, k);
}

int qr_path(int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);

        int nu = top[u];
        int L = id[nu], R = id[u];
        res += seg.qr(L, R).sum;

        u = fa[nu];
    }

    if (dep[u] < dep[v]) swap(u, v);
    res += seg.qr(id[v], id[u]).sum;
    return res;
}

int qr_tree(int u) {
    int L = id[u], R = id[u] + sz[u] - 1;
    return seg.qr(L, R).sum;
}

void solve() {
    dfs1(1, 0, 1);
    dfs2(1, 0, 1);
    seg.init(1, n);

    cin >> m;
    while (m--) {
        string op;
        cin >> op;
        if (op[0] == 'i') {
            int v;
            cin >> v;
            v++;

            int pre = qr_path(1, v);
            upd_path(1, v, 1);
            int t = qr_path(1, v) - pre;
            cout << t << "\n";
        } else {
            int u;
            cin >> u;
            u++;

            int t = qr_tree(u);
            upd_tree(u, 0);
            cout << t << "\n";
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

        for (int i = 2; i <= n; i++) {
            int p;
            cin >> p;
            p++;
            add(p, i);
        }

        solve();
    }

    return 0;
}