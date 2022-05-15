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
#include <cmath>
#include <random>
#include <cassert>

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

// region dsu
template<int SZ>
struct Dsu {
    int fa[SZ + 10];

    Dsu() {}

    void init(int _n) {
        iota(fa, fa + _n + 1, 0);
    }

    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }

    bool unite(int x, int y) {
        if (same(x, y)) return false;
        int tx = find(x), ty = find(y);
        fa[tx] = ty;
        return true;
    }

    bool same(int x, int y) {
        int tx = find(x), ty = find(y);
        return tx == ty;
    }
};
// endregion

// region 普通平衡树(fhq + 合并)
mt19937 rnd(random_device{}());
template<class Info, class Tag, int SZ>
struct Fhq {
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)

    Info (*plus)(const Info &p, const Info &a, const Info &b);
    int root[SZ + 10], cnt, mem;
    Info info[SZ + 10];

    Fhq() : plus(Info::plus) {}

    void init() {
        cnt = 0, mem = 0;
    }

    int new_tree() {
        int tid = ++cnt;
        assert(tid < SZ + 10);
        root[tid] = 0;
        return tid;
    }

    void xins(int &rt, int k) {
        int x, y;
        split(rt, info[k].val, x, y);
        rt = merge(merge(x, k), y);
    }

    void xdfs(int &k, int &rt) {
        if (!k) return;

        xdfs(ls(k), rt);
        xdfs(rs(k), rt);
        ls(k) = rs(k) = 0;
        info[k].sz = 1;
        xins(rt, k);
    }

    void xmerge(int tid1, int tid2) {
        int &rt1 = root[tid1], &rt2 = root[tid2];
        xdfs(rt1, rt2);
        rt1 = 0;
    }

    int new_node() {
        int id = ++mem;
        assert(id < SZ + 10);
        info[id] = Info();
        return id;
    }

    int size(int tid) {
        int rt = root[tid];
        return info[rt].sz;
    }

    void pull(int k) {
        info[k].set(plus(info[k], info[ls(k)], info[rs(k)]));
    }

    void split(int k, int val, int &x, int &y) {
        if (!k) {
            x = y = 0;
            return;
        }

        if (info[k].val <= val) {
            x = k;
            split(rs(k), val, rs(k), y);
        } else {
            y = k;
            split(ls(k), val, x, ls(k));
        }
        pull(k);
    }

    int merge(int x, int y) {
        if (!x || !y) return x | y;

        if (info[x].key > info[y].key) {
            rs(x) = merge(rs(x), y);
            pull(x);
            return x;
        } else {
            ls(y) = merge(x, ls(y));
            pull(y);
            return y;
        }
    }

    int build(int L, int R, Info a[]) {
        if (L > R) return 0;
        if (L == R) {
            int t = new_node();
            info[t] = a[L];
            info[t].init();
            return t;
        }

        int mid = L + R >> 1, k = new_node();
        info[k] = a[mid];
        info[k].init();
        ls(k) = build(L, mid - 1, a);
        rs(k) = build(mid + 1, R, a);
        pull(k);
        return k;
    }

    void insarr(int tid, int p, int len, Info a[]) {
        int &rt = root[tid];
        int x, y;
        split(rt, p, x, y);

        int nt = build(1, len, a);
        rt = merge(merge(x, nt), y);
    }

    void ins(int tid, const Info &v) {
        int &rt = root[tid];
        int x, y;
        split(rt, v.val, x, y);

        int t = new_node();
        info[t] = v;
        info[t].init();
        rt = merge(merge(x, t), y);
    }

    void del(int tid, int val) {
        int &rt = root[tid];
        int x, y, z;
        split(rt, val, x, z);
        split(x, val - 1, x, y);

        y = merge(ls(y), rs(y));
        rt = merge(merge(x, y), z);
    }

    int del_left(int tid, int val) {
        int &rt = root[tid];
        int x, y;
        split(rt, val, x, y);

        rt = y;
        return info[x].sz;
    }

    int del_right(int tid, int val) {
        int &rt = root[tid];
        int x, y;
        split(rt, val - 1, x, y);

        rt = x;
        return info[y].sz;
    }

    Info kth(int tid, int rk) {
        int rt = root[tid];
        if (rk < 1 || rk > info[rt].sz) return Info();

        int k = rt;
        while (k) {
            if (info[ls(k)].sz + 1 == rk) break;

            if (info[ls(k)].sz >= rk) {
                k = ls(k);
            } else {
                rk -= info[ls(k)].sz + 1;
                k = rs(k);
            }
        }

        return info[k];
    }

    int get_rk(int tid, int val) {
        int &rt = root[tid];
        int x, y;
        split(rt, val - 1, x, y);

        int res = info[x].sz + 1;

        rt = merge(x, y);
        return res;
    }

    Info get_pre(int tid, int val) {
        int &rt = root[tid];
        int x, y;
        split(rt, val - 1, x, y);

        int k = x;
        while (rs(k)) k = rs(k);
        Info res = info[k];
        if (info[k].sz == 0) res.val = -1e9;

        rt = merge(x, y);
        return res;
    }

    Info get_nxt(int tid, int val) {
        int &rt = root[tid];
        int x, y;
        split(rt, val, x, y);

        int k = y;
        while (ls(k)) k = ls(k);
        Info res = info[k];
        if (info[k].sz == 0) res.val = 1e9;

        rt = merge(x, y);
        return res;
    }
};
// endregion

// region 文艺平衡树(fhq)
struct Tag {
    int x;

    Tag(int x = 0) : x(x) {}

    bool check() const {
        return x != 0;
    }

    void apply(const Tag &a) {
        if (!a.check()) return;
        x ^= a.x;
    }
};

struct Info {
    int lson, rson, key, val;
    int sz, id;

    Info(int val = 0, int sz = 0, int id = 0) : lson(0), rson(0), val(val), sz(sz), id(id) {}

    void init() {
        key = rnd();
    }

    void apply(const Tag &a) {
        if (!a.check()) return;
        swap(lson, rson);
    }

    static Info plus(const Info &p, const Info &a, const Info &b) {
        return {0, a.sz + b.sz + 1, 0};
    }

    void set(const Info &a) {
        sz = a.sz;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 100010;
const int M = 300010;

int n, m;
int a[N];
pii b[M];
Dsu<N> dsu;
Fhq<Info, Tag, N> fhq;

void solve() {
    dsu.init(n);
    for (int i = 1; i <= n; i++) {
        int tid = fhq.new_tree();
        fhq.ins(tid, {a[i], 1, i});
    }
    for (int i = 1; i <= m; i++) {
        auto [x, y] = b[i];

        int tx = dsu.find(x), ty = dsu.find(y);
        if (fhq.size(tx) > fhq.size(ty)) swap(tx, ty);

        fhq.xmerge(tx, ty), dsu.unite(tx, ty);
    }

    int q;
    cin >> q;
    while (q--) {
        string op;
        int x, y;
        cin >> op >> x >> y;

        if (op == "B") {
            int tx = dsu.find(x), ty = dsu.find(y);
            if (fhq.size(tx) > fhq.size(ty)) swap(tx, ty);
            fhq.xmerge(tx, ty), dsu.unite(tx, ty);
        }
        if (op == "Q") {
            int tx = dsu.find(x);
            auto t = fhq.kth(tx, y);
            if (t.sz == 0) cout << -1 << "\n";
            else cout << t.id << "\n";
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) cin >> b[i].fi >> b[i].se;
        solve();
    }

    return 0;
}