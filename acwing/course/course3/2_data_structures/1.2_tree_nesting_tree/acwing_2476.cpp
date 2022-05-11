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
    int pv, nv;

    Tag(int pv = -1, int nv = -1) : pv(pv), nv(nv) {}

    bool check() const {
        return pv != -1;
    }

    void apply(const Tag &a) {
        if (!a.check()) return;
    }
};

struct Info {
    int lson, rson, key, val;
    int sz;

    Info(int val = 0, int sz = 0) : lson(0), rson(0), val(val), sz(sz) {}

    void init() {
        key = rnd();
    }

    void apply(const Tag &a) {
        if (!a.check()) return;
        swap(lson, rson);
    }

    static Info plus(const Info &p, const Info &a, const Info &b) {
        return {0, a.sz + b.sz + 1};
    }

    void set(const Info &a) {
        sz = a.sz;
    }
};
// endregion

// region 线段树 套 x
template<class OInfo, class Info, class Tag, int SZ>
struct OSeg {
#define mid (s + e >> 1)
#define ls(x) (oinfo[x].lson)
#define rs(x) (oinfo[x].rson)

    int lb, rb, rt, mem;
    OInfo oinfo[SZ * 4];

    OSeg() {}

    void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        oinfo[0] = OInfo();
    }

    int new_node() {
        int id = ++mem;
        oinfo[id] = OInfo();
        return id;
    }

    void upd(int id, int pv, int nv) {
        upd(rt, lb, rb, id, pv, nv);
    }

    void upd(int &k, int s, int e, int id, int pv, int nv) {
        if (!k) k = new_node();

        oinfo[k].apply(pv, nv);
        if (s == e) return;

        if (id <= mid) upd(ls(k), s, mid, id, pv, nv);
        if (id >= mid + 1) upd(rs(k), mid + 1, e, id, pv, nv);
    }

    void build(int L, int R, int a[]) {
        build(rt, L, R, a);
    }

    void build(int &k, int s, int e, int a[]) {
        if (!k) k = new_node();

        oinfo[k].init(s, e, a);
        if (s == e) return;
        build(ls(k), s, mid, a), build(rs(k), mid + 1, e, a);
    }

    int get_rk(int L, int R, int x) {
        return get_rk(rt, lb, rb, L, R, x) + 1;
    }

    int get_rk(int k, int s, int e, int L, int R, int x) {
        if (L <= s && e <= R) return oinfo[k].get_rk(x);

        if (R <= mid) return get_rk(ls(k), s, mid, L, R, x);
        if (L >= mid + 1) return get_rk(rs(k), mid + 1, e, L, R, x);
        return get_rk(ls(k), s, mid, L, R, x) + get_rk(rs(k), mid + 1, e, L, R, x);
    }

    int get_kth(int L, int R, int x) {
        int left = 0, right = 1e8;
        while (left < right) {
            int md = left + right + 1 >> 1;
            int t = get_rk(L, R, md);
            if (t <= x) left = md;
            else right = md - 1;
        }
    }

    int get_pre(int L, int R, int x) {
        return get_pre(rt, lb, rb, L, R, x);
    }

    int get_pre(int k, int s, int e, int L, int R, int x) {
        if (L <= s && e <= R) return oinfo[k].get_pre(x);

        if (R <= mid) return get_pre(ls(k), s, mid, L, R, x);
        if (L >= mid + 1) return get_pre(rs(k), mid + 1, e, L, R, x);
        return max(get_pre(ls(k), s, mid, L, R, x), get_pre(rs(k), mid + 1, e, L, R, x));
    }

    int get_nxt(int L, int R, int x) {
        return get_nxt(rt, lb, rb, L, R, x);
    }

    int get_nxt(int k, int s, int e, int L, int R, int x) {
        if (L <= s && e <= R) return oinfo[k].get_nxt(x);

        if (R <= mid) return get_nxt(ls(k), s, mid, L, R, x);
        if (L >= mid + 1) return get_nxt(rs(k), mid + 1, e, L, R, x);
        return min(get_nxt(ls(k), s, mid, L, R, x), get_nxt(rs(k), mid + 1, e, L, R, x));
    }
};
// endregion

// region x 套 普通平衡树(fhq)
Fhq<Info, Tag, 50000 * 40> fhq;

struct OInfo {
    int lson, rson;
    int tid;

    OInfo() : lson(0), rson(0) {}

    void init(int s, int e, int a[]) {
        static Info buf[50010];

        for (int i = s; i <= e; i++) {
            Info t = Info();
            t.val = a[i];
            t.sz = 1;
            t.init();

            buf[i] = t;
        }
        sort(buf + s, buf + e + 1, [](auto &a, auto &b) {
            return a.val < b.val;
        });

        tid = fhq.new_tree();
        fhq.root[tid] = fhq.build(s, e, buf);
    }

    void apply(int pv, int nv) {
        fhq.del(tid, pv);

        Info t = Info();
        t.val = nv;
        t.sz = 1;
        t.init();
        fhq.ins(tid, t);
    }

    int get_rk(int x) {
        return fhq.get_rk(tid, x) - 1;
    }

    int get_pre(int x) {
        return fhq.get_pre(tid, x).val;
    }

    int get_nxt(int x) {
        int t = fhq.get_nxt(tid, x).val;
        return t;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 5e4 + 10;

int n, m;
int a[N];
OSeg<OInfo, Info, Tag, N> seg;

void solve() {
    seg.init(1, n);
    seg.build(1, n, a);

    while (m--) {
        int op;
        cin >> op;

        if (op == 1) {
            int L, R, x;
            cin >> L >> R >> x;

            cout << seg.get_rk(L, R, x) << "\n";
        }
        if (op == 2) {
            int L, R, x;
            cin >> L >> R >> x;

            cout << seg.get_kth(L, R, x) << "\n";
        }
        if (op == 3) {
            int p, x;
            cin >> p >> x;

            seg.upd(p, a[p], x);
            a[p] = x;
        }
        if (op == 4) {
            int L, R, x;
            cin >> L >> R >> x;

            cout << seg.get_pre(L, R, x) << "\n";
        }
        if (op == 5) {
            int L, R, x;
            cin >> L >> R >> x;

            cout << seg.get_nxt(L, R, x) << "\n";
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
        solve();
    }

    return 0;
}