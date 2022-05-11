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
        assert(id < SZ * 4);
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

// region x 套 线段树
Seg<Info, Tag, 50000 * 80> seg;

struct OInfo {
    int lson, rson;
    int tid;

    OInfo() : lson(0), rson(0) {
        tid = seg.new_tree();
    }

    void init(int s, int e, int a[]) {}

    void apply(int L, int R) {
        seg.upd(tid, L, R, 1);
    }

    ll get(int L, int R) {
        return seg.qr(tid, L, R).sum;
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

// region x 套 set
struct Tag {
    int pv, nv;

    Tag(int pv = -1, int nv = -1) : pv(pv), nv(nv) {}
};

using Info = int;

struct OInfo {
    int lson, rson;
    multiset<int> st;

    OInfo() : lson(0), rson(0) {}

    void init(int s, int e, int a[]) {
        for (int i = s; i <= e; i++) st.insert(a[i]);
        st.insert(-1e9), st.insert(1e9);
    }

    void apply(const Tag &a) {
        st.erase(st.find(a.pv));
        st.insert(a.nv);
    }

    int get_pre(int x) {
        auto it = st.lower_bound(x);
        it = prev(it);
        return *it;
    }
};
// endregion
