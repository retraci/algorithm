// region 普通平衡树(fenwick)
template<int SZ>
struct Fenwick {
    int n, sz;
    ll tr[SZ + 10];

    Fenwick() {}

    void init(int _n, ll v = 0) {
        n = _n, sz = 0;
        fill(tr, tr + n + 1, v);
    }

    int size() {
        return sz;
    }

    void upd(int id, ll x) {
        sz += x;
        for (int i = id; i <= n; i += i & -i) tr[i] += x;
    }

    ll qr(int id) {
        ll res = 0;
        for (int i = id; i; i -= i & -i) res += tr[i];
        return res;
    }

    int kth(int x) {
        if (x < 1 || x > sz) return 1e9;

        int pos = 0;
        for (int i = __lg(n); i >= 0; i--) {
            if (pos + (1 << i) <= n && tr[pos + (1 << i)] < x) {
                pos += 1 << i;
                x -= tr[pos];
            }
        }

        return pos + 1;
    }

    int get_rk(int x) {
        return qr(x - 1) + 1;
    }

    int get_pre(int x) {
        return kth(qr(x - 1));
    }

    int get_nxt(int x) {
        return kth(qr(x) + 1);
    }
};
// endregion

// region 普通平衡树(fhq)
mt19937 rnd(random_device{}());
template<class Info, class Tag, int SZ>
struct Fhq {
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)

    Info (*plus)(const Info &p, const Info &a, const Info &b);
    int rt, mem;
    Info info[SZ + 10];

    Fhq() : plus(Info::plus) {}

    void init() {
        rt = 0, mem = 0;
        info[0] = Info();
    }

    int new_node() {
        int id = ++mem;
        assert(id < SZ + 10);
        info[id] = Info();
        return id;
    }

    int size() {
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

    void insarr(int p, int len, Info a[]) {
        int x, y;
        split(rt, p, x, y);

        int nt = build(1, len, a);
        rt = merge(merge(x, nt), y);
    }

    void ins(const Info &v) {
        int x, y;
        split(rt, v.val, x, y);

        int t = new_node();
        info[t] = v;
        info[t].init();
        rt = merge(merge(x, t), y);
    }

    void del(int val) {
        int x, y, z;
        split(rt, val - 1, x, y);
        split(y, val, y, z);

        y = merge(ls(y), rs(y));
        rt = merge(merge(x, y), z);
    }

    int del_left(int val) {
        int x, y;
        split(rt, val, x, y);

        rt = y;
        return info[x].sz;
    }

    int del_right(int val) {
        int x, y;
        split(rt, val - 1, x, y);

        rt = x;
        return info[y].sz;
    }

    Info kth(int rk) {
        if (rk < 1 || rk > size()) return Info();

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

    int get_rk(int val) {
        int x, y;
        split(rt, val - 1, x, y);

        int res = info[x].sz + 1;

        rt = merge(x, y);
        return res;
    }

    Info get_pre(int val) {
        int x, y;
        split(rt, val - 1, x, y);

        int k = x;
        while (rs(k)) k = rs(k);
        Info res = info[k];
        if (info[k].sz == 0) res.val = -1e9;

        rt = merge(x, y);
        return res;
    }

    Info get_nxt(int val) {
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

// region 普通平衡树(fhq + 启发式合并)
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

// region 维护序列(fhq)
mt19937 rnd(random_device{}());
template<class Info, class Tag, int SZ>
struct Fhq {
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)

    Info (*plus)(const Info &p, const Info &a, const Info &b);
    int n, rt, mem;
    Info info[SZ + 10];
    Tag tag[SZ + 10];

    Fhq() : plus(Info::plus) {}

    void init() {
        rt = 0, mem = 0;
        info[0] = Info();
        tag[0] = Tag();
    }

    int new_node() {
        int id = ++mem;
        assert(id < SZ + 10);
        info[id] = Info();
        tag[id] = Tag();
        return id;
    }

    int size() {
        return info[rt].sz;
    }

    void pull(int k) {
        info[k].set(plus(info[k], info[ls(k)], info[rs(k)]));
    }

    void apply(int k, const Tag &v) {
        info[k].apply(v);
        tag[k].apply(v);
    }

    void push(int k) {
        if (tag[k].check()) {
            if (ls(k)) apply(ls(k), tag[k]);
            if (rs(k)) apply(rs(k), tag[k]);
            tag[k] = Tag();
        }
    }

    void split(int k, int sz, int &x, int &y) {
        if (!k) {
            x = y = 0;
            return;
        }

        push(k);
        if (info[ls(k)].sz < sz) {
            x = k;
            split(rs(k), sz - info[ls(k)].sz - 1, rs(k), y);
        } else {
            y = k;
            split(ls(k), sz, x, ls(k));
        }
        pull(k);
    }

    int merge(int x, int y) {
        if (!x || !y) return x | y;

        if (info[x].key > info[y].key) {
            push(x);
            rs(x) = merge(rs(x), y);
            pull(x);
            return x;
        } else {
            push(y);
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

    void insarr(int p, int len, Info a[]) {
        int x, y;
        split(rt, p, x, y);

        int nt = build(1, len, a);
        rt = merge(merge(x, nt), y);
    }

    void ins(int p, const Info &v) {
        int x, y;
        split(rt, p, x, y);

        int t = new_node();
        info[t] = v;
        info[t].init();
        rt = merge(merge(x, t), y);
    }

    void del(int L, int R) {
        int x, y, z;
        split(rt, L - 1, x, y);
        split(y, R - L + 1, y, z);

        rt = merge(x, z);
    }

    void upd(int L, int R, const Tag &v) {
        int x, y, z;
        split(rt, L - 1, x, y);
        split(y, R - L + 1, y, z);

        apply(y, v);
        rt = merge(merge(x, y), z);
    }

    Info qr(int L, int R) {
        int x, y, z;
        split(rt, L - 1, x, y);
        split(y, R - L + 1, y, z);

        Info res = info[y];
        rt = merge(merge(x, y), z);
        return res;
    }

    void dump(int k, vector<Info> &seq) {
        if (!k) return;

        push(k);
        dump(ls(k), seq);
        seq.push_back(info[k]);
        dump(rs(k), seq);
    }

    vector<Info> dump() {
        vector<Info> res;
        dump(rt, res);
        return res;
    }
};
// endregion

// region 维护序列(fhq + gc)
mt19937 rnd(random_device{}());
template<class Info, class Tag, int SZ>
struct Fhq {
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)

    Info (*plus)(const Info &p, const Info &a, const Info &b);
    int n, rt, mem[SZ + 10], tp;
    Info info[SZ + 10];
    Tag tag[SZ + 10];

    Fhq() : plus(Info::plus) {}

    void init() {
        rt = 0, tp = SZ;
        iota(mem, mem + SZ + 1, 0);
        info[0] = Info();
        tag[0] = Tag();
    }

    int new_node() {
        assert(tp >= 0);
        int id = mem[tp--];
        info[id] = Info();
        tag[id] = Tag();
        return id;
    }

    void del_node(int k) {
        if (!k) return;
        mem[++tp] = k;
        if (ls(k)) del_node(ls(k));
        if (rs(k)) del_node(rs(k));
    }

    int size() {
        return info[rt].sz;
    }

    void pull(int k) {
        info[k].set(plus(info[k], info[ls(k)], info[rs(k)]));
    }

    void apply(int k, const Tag &v) {
        info[k].apply(v);
        tag[k].apply(v);
    }

    void push(int k) {
        if (tag[k].check()) {
            if (ls(k)) apply(ls(k), tag[k]);
            if (rs(k)) apply(rs(k), tag[k]);
            tag[k] = Tag();
        }
    }

    void split(int k, int sz, int &x, int &y) {
        if (!k) {
            x = y = 0;
            return;
        }

        push(k);
        if (info[ls(k)].sz < sz) {
            x = k;
            split(rs(k), sz - info[ls(k)].sz - 1, rs(k), y);
        } else {
            y = k;
            split(ls(k), sz, x, ls(k));
        }
        pull(k);
    }

    int merge(int x, int y) {
        if (!x || !y) return x | y;

        if (info[x].key > info[y].key) {
            push(x);
            rs(x) = merge(rs(x), y);
            pull(x);
            return x;
        } else {
            push(y);
            ls(y) = merge(x, ls(y));
            pull(y);
            return y;
        }
    }

    int build(int L, int R, Info a[]) {
        if (L > R) return 0;
        if (L == R) {
            int k = new_node();
            info[k] = a[L];
            info[k].init();
            return k;
        }

        int mid = L + R >> 1, p = new_node();
        info[p] = a[mid];
        info[p].init();
        ls(p) = build(L, mid - 1, a);
        rs(p) = build(mid + 1, R, a);
        pull(p);
        return p;
    }

    void insarr(int p, int len, Info a[]) {
        int x, y;
        split(rt, p, x, y);

        int nt = build(1, len, a);
        rt = merge(merge(x, nt), y);
    }

    void ins(int p, const Info &v) {
        int x, y;
        split(rt, p, x, y);

        int t = new_node();
        info[t] = v;
        info[t].init();
        rt = merge(merge(x, t), y);
    }

    void del(int L, int R) {
        int x, y, z;
        split(rt, L - 1, x, y);
        split(y, R - L + 1, y, z);

        del_node(y);
        rt = merge(x, z);
    }

    void upd(int L, int R, const Tag &v) {
        int x, y, z;
        split(rt, L - 1, x, y);
        split(y, R - L + 1, y, z);

        apply(y, v);
        rt = merge(merge(x, y), z);
    }

    Info qr(int L, int R) {
        int x, y, z;
        split(rt, L - 1, x, y);
        split(y, R - L + 1, y, z);

        Info res = info[y];
        rt = merge(merge(x, y), z);
        return res;
    }

    void dump(int k, vector<Info> &seq) {
        if (!k) return;

        push(k);
        dump(ls(k), seq);
        seq.push_back(info[k]);
        dump(rs(k), seq);
    }

    vector<Info> dump() {
        vector<Info> res;
        dump(rt, res);
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