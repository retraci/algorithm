// region 普通线段树
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        ll sum, lz;
    };

    int lb, rb, rt, mem;
    Node tr[SZ * 4];

    inline Seg() {
        init(1, SZ);
    }

    inline void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        tr[0].lson = tr[0].rson = 0;
        tr[0].sum = 0;
        tr[0].lz = 0;
    }

    inline void init(int L, int R, ll val) {
        init(L, R);
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        tr[id].sum = 0;
        tr[id].lz = 0;
        return id;
    }

    inline void pull(Node &fa, Node &lc, Node &rc) {
        fa.sum = lc.sum + rc.sum;
    }

    inline void pull(int k) {
        pull(tr[k], tr[ls(k)], tr[rs(k)]);
    }

    inline void apply(Node &t, ll sz, ll val) {
        t.sum = t.sum + sz * val;
        t.lz = t.lz + val;
    }

    inline void push(int k, int s, int e) {
        ll len = e - s + 1;
        ll lsz = len - len / 2, rsz = len / 2;
        if (tr[k].lz) {
            if (!ls(k)) ls(k) = new_node();
            if (!rs(k)) rs(k) = new_node();
            apply(tr[ls(k)], lsz, tr[k].lz);
            apply(tr[rs(k)], rsz, tr[k].lz);
            tr[k].lz = 0;
        }
    }

    inline void add(int &k, int s, int e, int L, int R, ll val) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            apply(tr[k], e - s + 1, val);
            return;
        }

        push(k, s, e);
        if (L <= mid) add(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) add(rs(k), mid + 1, e, L, R, val);
        pull(k);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = val;
            return;
        }

        push(k, s, e);
        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        pull(k);
    }

    inline Node query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k];

        push(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        Node res = {0};
        Node lc = query(ls(k), s, mid, L, R);
        Node rc = query(rs(k), mid + 1, e, L, R);
        pull(res, lc, rc);
        return res;
    }

    inline ll query_kth(int k, int s, int e, int x) {
        if (s == e) return s;

        if (x <= tr[ls(k)].sum) return query_kth(ls(k), s, mid, x);
        else return query_kth(rs(k), mid + 1, e, x - tr[ls(k)].sum);
    }

    inline void add(int L, int R, ll val) {
        if (R < L) return;
        add(rt, lb, rb, L, R, val);
    }

    inline void set(int id, ll val) {
        set(rt, lb, rb, id, val);
    }

    inline Node query(int L, int R) {
        if (R < L) return {0};
        return query(rt, lb, rb, L, R);
    }

    inline ll query_kth(int x) {
        return query_kth(rt, lb, rb, x);
    }
};
// endregion

// region 区间最大值段树
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        ll sum, lz;
    };

    int lb, rb, rt, mem;
    Node tr[SZ * 4];

    inline Seg() {
        init(1, SZ);
    }

    inline void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        tr[0].lson = tr[0].rson = 0;
        tr[0].sum = tr[0].lz = 0;
    }

    inline void init(int L, int R, ll val) {
        init(L, R);
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        tr[id].sum = 0;
        tr[id].lz = 0;
        return id;
    }

    inline void pull(Node &fa, Node &lc, Node &rc) {
        fa.sum = max(lc.sum, rc.sum);
    }

    inline void pull(int k) {
        pull(tr[k], tr[ls(k)], tr[rs(k)]);
    }

    inline void apply(Node &t, ll val) {
        t.sum = max(t.sum, val);
        t.lz = max(t.lz, val);
    }

    inline void push(int k, int s, int e) {
        if (tr[k].lz) {
            if (!ls(k)) ls(k) = new_node();
            if (!rs(k)) rs(k) = new_node();
            apply(tr[ls(k)], tr[k].lz);
            apply(tr[rs(k)], tr[k].lz);
            tr[k].lz = 0;
        }
    }

    inline void update(int &k, int s, int e, int L, int R, ll val) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            apply(tr[k], val);
            return;
        }

        push(k, s, e);
        if (L <= mid) update(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) update(rs(k), mid + 1, e, L, R, val);
        pull(k);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = val;
            return;
        }

        push(k, s, e);
        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        pull(k);
    }

    inline Node query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k];

        push(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        Node res = {0};
        Node lc = query(ls(k), s, mid, L, R);
        Node rc = query(rs(k), mid + 1, e, L, R);
        pull(res, lc, rc);
        return res;
    }

    inline void update(int L, int R, ll val) {
        if (R < L) return;
        update(rt, lb, rb, L, R, val);
    }

    inline void set(int id, ll val) {
        set(rt, lb, rb, id, val);
    }

    inline Node query(int L, int R) {
        if (R < L) return {0};
        return query(rt, lb, rb, L, R);
    }
};
// endregion

// region 区间最小值段树
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        ll sum, lz;
    };

    int lb, rb, rt, mem;
    Node tr[SZ * 4];

    inline Seg() {
        init(1, SZ);
    }

    inline void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        tr[0].lson = tr[0].rson = 0;
        tr[0].sum = tr[0].lz = 1e18;
    }

    inline void init(int L, int R, ll val) {
        init(L, R);
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        tr[id].sum = tr[id].lz = 1e18;
        return id;
    }

    inline void pull(Node &fa, Node &lc, Node &rc) {
        fa.sum = min(lc.sum, rc.sum);
    }

    inline void pull(int k) {
        pull(tr[k], tr[ls(k)], tr[rs(k)]);
    }

    inline void apply(Node &t, ll val) {
        t.sum = min(t.sum, val);
        t.lz = min(t.lz, val);
    }

    inline void push(int k, int s, int e) {
        if (tr[k].lz != 1e18) {
            if (!ls(k)) ls(k) = new_node();
            if (!rs(k)) rs(k) = new_node();
            apply(tr[ls(k)], tr[k].lz);
            apply(tr[rs(k)], tr[k].lz);
            tr[k].lz = 1e18;
        }
    }

    inline void update(int &k, int s, int e, int L, int R, ll val) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            apply(tr[k], val);
            return;
        }

        push(k, s, e);
        if (L <= mid) update(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) update(rs(k), mid + 1, e, L, R, val);
        pull(k);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = val;
            return;
        }

        push(k, s, e);
        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        pull(k);
    }

    inline Node query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k];

        push(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        Node res = {0, 0, (ll) 1e18, 0};
        Node lc = query(ls(k), s, mid, L, R);
        Node rc = query(rs(k), mid + 1, e, L, R);
        pull(res, lc, rc);
        return res;
    }

    inline void update(int L, int R, ll val) {
        if (R < L) return;
        update(rt, lb, rb, L, R, val);
    }

    inline void set(int id, ll val) {
        set(rt, lb, rb, id, val);
    }

    inline Node query(int L, int R) {
        if (R < L) return {0, 0, (ll) 1e18, 0};
        return query(rt, lb, rb, L, R);
    }
};
// endregion

// region 区间修改, 维护最大值线段树
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        ll sum, lz, mx;
    };

    int lb, rb, rt, mem;
    Node tr[SZ * 4];

    inline Seg() {
        init(1, SZ);
    }

    inline void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        tr[0].lson = tr[0].rson = 0;
        tr[0].sum = tr[0].lz = tr[0].mx = 0;
    }

    inline void init(int L, int R, ll val) {
        init(L, R);
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        tr[id].sum = tr[id].lz = tr[id].mx = 0;
        return id;
    }

    inline void pull(Node &fa, Node &lc, Node &rc) {
        fa.sum = lc.sum + rc.sum;
        fa.mx = max(lc.mx, rc.mx);
    }

    inline void pull(int k) {
        pull(tr[k], tr[ls(k)], tr[rs(k)]);
    }

    inline void apply(Node &t, ll sz, ll val) {
        t.sum = t.sum + sz * val;
        t.lz = t.lz + val;
        t.mx = t.mx + val;
    }

    inline void push(int k, int s, int e) {
        ll len = e - s + 1;
        ll lsz = len - len / 2, rsz = len / 2;
        if (tr[k].lz) {
            if (!ls(k)) ls(k) = new_node();
            if (!rs(k)) rs(k) = new_node();
            apply(tr[ls(k)], lsz, tr[k].lz);
            apply(tr[rs(k)], rsz, tr[k].lz);
            tr[k].lz = 0;
        }
    }

    inline void add(int &k, int s, int e, int L, int R, ll val) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            apply(tr[k], e - s + 1, val);
            return;
        }

        push(k, s, e);
        if (L <= mid) add(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) add(rs(k), mid + 1, e, L, R, val);
        pull(k);
    }

    inline void update(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = tr[k].mx = max(tr[k].mx, val);
            return;
        }

        push(k, s, e);
        if (id <= mid) update(ls(k), s, mid, id, val);
        if (id >= mid + 1) update(rs(k), mid + 1, e, id, val);
        pull(k);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = tr[k].mx = val;
            return;
        }

        push(k, s, e);
        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        pull(k);
    }

    inline Node query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k];

        push(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        Node res = {0};
        Node lc = query(ls(k), s, mid, L, R);
        Node rc = query(rs(k), mid + 1, e, L, R);
        pull(res, lc, rc);
        return res;
    }

    inline void add(int L, int R, ll val) {
        if (R < L) return;
        add(rt, lb, rb, L, R, val);
    }

    inline void update(int id, ll val) {
        update(rt, lb, rb, id, val);
    }

    inline void set(int id, ll val) {
        set(rt, lb, rb, id, val);
    }

    inline Node query(int L, int R) {
        if (R < L) return {0};
        return query(rt, lb, rb, L, R);
    }
};
// endregion

// region 区间修改, 维护最小值线段树
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        ll sum, lz, mi;
    };

    int lb, rb, rt, mem;
    Node tr[SZ * 4];

    inline Seg() {
        init(1, SZ);
    }

    inline void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        tr[0].lson = tr[0].rson = 0;
        tr[0].sum = tr[0].lz = tr[0].mi = 0;
    }

    inline void init(int L, int R, ll val) {
        init(L, R);
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        tr[id].sum = tr[id].lz = tr[id].mi = 0;
        return id;
    }

    inline void pull(Node &fa, Node &lc, Node &rc) {
        fa.sum = lc.sum + rc.sum;
        fa.mi = min(lc.mi, rc.mi);
    }

    inline void pull(int k) {
        pull(tr[k], tr[ls(k)], tr[rs(k)]);
    }

    inline void apply(Node &t, ll sz, ll val) {
        t.sum = t.sum + sz * val;
        t.lz = t.lz + val;
        t.mi = t.mi + val;
    }

    inline void push(int k, int s, int e) {
        ll len = e - s + 1;
        ll lsz = len - len / 2, rsz = len / 2;
        if (tr[k].lz) {
            if (!ls(k)) ls(k) = new_node();
            if (!rs(k)) rs(k) = new_node();
            apply(tr[ls(k)], lsz, tr[k].lz);
            apply(tr[rs(k)], rsz, tr[k].lz);
            tr[k].lz = 0;
        }
    }

    inline void add(int &k, int s, int e, int L, int R, ll val) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            apply(tr[k], e - s + 1, val);
            return;
        }

        push(k, s, e);
        if (L <= mid) add(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) add(rs(k), mid + 1, e, L, R, val);
        pull(k);
    }

    inline void update(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = tr[k].mi = min(tr[k].mi, val);
            return;
        }

        push(k, s, e);
        if (id <= mid) update(ls(k), s, mid, id, val);
        if (id >= mid + 1) update(rs(k), mid + 1, e, id, val);
        pull(k);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = tr[k].mi = val;
            return;
        }

        push(k, s, e);
        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        pull(k);
    }

    inline Node query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k];

        push(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        Node res = {0};
        Node lc = query(ls(k), s, mid, L, R);
        Node rc = query(rs(k), mid + 1, e, L, R);
        pull(res, lc, rc);
        return res;
    }

    inline void add(int L, int R, ll val) {
        if (R < L) return;
        add(rt, lb, rb, L, R, val);
    }

    inline void update(int id, ll val) {
        update(rt, lb, rb, id, val);
    }

    inline void set(int id, ll val) {
        set(rt, lb, rb, id, val);
    }

    inline Node query(int L, int R) {
        if (R < L) return {0};
        return query(rt, lb, rb, L, R);
    }
};
// endregion

// region 区间开关, 维护最值线段树, 1: 开, 0: 关
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
        tr[0].mx = tr[0].mx_bak = 0;
        tr[0].mi = tr[0].mi_bak = 1e9;
        tr[0].lz = -1;
    }

    inline void init(int L, int R, ll val) {
        init(L, R);
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        tr[id].mx = tr[id].mx_bak = 0;
        tr[id].mi = tr[id].mi_bak = 1e9;
        tr[id].lz = -1;
        return id;
    }

    inline void pull(Node &fa, Node &lc, Node &rc) {
        fa.mx = max(lc.mx, rc.mx);
        fa.mx_bak = max(lc.mx_bak, rc.mx_bak);
        fa.mi = min(lc.mi, rc.mi);
        fa.mi_bak = min(lc.mi_bak, rc.mi_bak);
    }

    inline void pull(int k) {
        pull(tr[k], tr[ls(k)], tr[rs(k)]);
    }

    inline void apply(Node &t, ll col) {
        t.lz = col;
        if (col) {
            t.mx = t.mx_bak;
            t.mi = t.mi_bak;
        } else {
            t.mx = 0, t.mi = 1e9;
        }
    }

    inline void push(int k, int s, int e) {
        if (~tr[k].lz) {
            if (!ls(k)) ls(k) = new_node();
            if (!rs(k)) rs(k) = new_node();
            apply(tr[ls(k)], tr[k].lz);
            apply(tr[rs(k)], tr[k].lz);
            tr[k].lz = -1;
        }
    }

    inline void add(int &k, int s, int e, int L, int R, ll col) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            apply(tr[k], col);
            return;
        }

        push(k, s, e);
        if (L <= mid) add(ls(k), s, mid, L, R, col);
        if (R >= mid + 1) add(rs(k), mid + 1, e, L, R, col);
        pull(k);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].mi_bak = tr[k].mx_bak = val;
            return;
        }

        push(k, s, e);
        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        pull(k);
    }

    inline Node query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k];

        push(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        Node res = {0, 0, 0, 0, (ll) 1e9, 0};
        Node lc = query(ls(k), s, mid, L, R);
        Node rc = query(rs(k), mid + 1, e, L, R);
        pull(res, lc, rc);
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

// region 扫描线线段树
vector<ll> lsh;

int get_id(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        ll sum, v;
    };

    int lb, rb, rt, mem;
    Node tr[SZ * 4];

    inline Seg() {
        init(1, SZ);
    }

    inline void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        tr[0].lson = tr[0].rson = 0;
        tr[0].sum = tr[0].v = 0;
    }

    inline void init(int L, int R, ll val) {
        init(L, R);
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        tr[id].sum = tr[id].v = 0;
        return id;
    }

    inline void pull(int k, int s, int e) {
        if (tr[k].sum) tr[k].v = lsh[e + 1] - lsh[s];
        else if (s != e) tr[k].v = tr[ls(k)].v + tr[rs(k)].v;
        else tr[k].v = 0;
    }

    inline void add(int &k, int s, int e, int L, int R, ll val) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            tr[k].sum = tr[k].sum + val;
            pull(k, s, e);
            return;
        }

        if (L <= mid) add(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) add(rs(k), mid + 1, e, L, R, val);
        pull(k, s, e);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = val;
            pull(k, s, e);
            return;
        }

        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        pull(k, s, e);
    }

    inline ll query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k].v;

        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        return query(ls(k), s, mid, L, R) + query(rs(k), mid + 1, e, L, R);
    }

    inline void add(int L, int R, ll val) {
        if (R < L) return;
        add(rt, lb, rb, L, R, val);
    }

    inline void set(int id, ll val) {
        set(rt, lb, rb, id, val);
    }

    inline ll query(int L, int R) {
        if (R < L) return 0;
        return query(rt, lb, rb, L, R);
    }
};
// endregion

// region 线段树分裂
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    const ll MOD = 1e9 + 7;

    struct Node {
        int lson, rson;
        ll sum, lz;
    };

    int lb, rb, mem;
    Node tr[SZ * 40];
    int root[SZ + 1], cnt;

    inline Seg() {
        mem = 0, lb = 1, rb = SZ;
    }

    inline void init(int L = 1, int R = SZ, int _cnt = 0) {
        lb = L, rb = R, cnt = _cnt;
    }

    inline void merge(int &x, int y) {
        if (!x || !y) {
            x |= y;
            return;
        }

        tr[x].sum += tr[y].sum;
        tr[x].lz += tr[y].lz;
        merge(ls(x), ls(y));
        merge(rs(x), rs(y));
    }

    inline int split(int &k, int s, int e, int L, int R) {
        int id = new_node();
        if (L <= s && R >= e) {
            tr[id] = tr[k];
            k = 0;
        } else {
            if (L <= mid) tr[id].lson = split(ls(k), s, mid, L, R);
            if (R >= mid + 1) tr[id].rson = split(rs(k), mid + 1, e, L, R);
            pull(k), pull(id);
        }
        return id;
    }

    inline int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        return id;
    }

    inline void pull(int k) {
        tr[k].sum = tr[ls(k)].sum + tr[rs(k)].sum;
    }

    inline void push(int k, int s, int e) {
        if (!ls(k)) ls(k) = new_node();
        if (!rs(k)) rs(k) = new_node();
        ll len = e - s + 1;
        ll lsz = len - len / 2, rsz = len / 2;
        if (tr[k].lz) {
            tr[ls(k)].sum = tr[ls(k)].sum + lsz * tr[k].lz;
            tr[rs(k)].sum = tr[rs(k)].sum + rsz * tr[k].lz;
            tr[ls(k)].lz = tr[ls(k)].lz + tr[k].lz;
            tr[rs(k)].lz = tr[rs(k)].lz + tr[k].lz;
            tr[k].lz = 0;
        }
    }

    inline void update(int &k, int s, int e, int L, int R, ll val) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            tr[k].sum = tr[k].sum + (R - L + 1) * val;
            tr[k].lz = tr[k].lz + val;
            return;
        }

        push(k, s, e);
        if (L <= mid) update(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) update(rs(k), mid + 1, e, L, R, val);
        pull(k);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = val;
            return;
        }

        push(k, s, e);
        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        pull(k);
    }

    inline ll query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k].sum;

        push(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        return query(ls(k), s, mid, L, R) + query(rs(k), mid + 1, e, L, R);
    }

    inline ll query(int k, int s, int e, int x) {
        if (s == e) return s;
        push(k, s, e);
        if (x <= tr[ls(k)].sum) return query(ls(k), s, mid, x);
        else return query(rs(k), mid + 1, e, x - tr[ls(k)].sum);
    }

    inline int split(int &k, int L, int R) {
        if (R < L) return -1;
        return split(k, lb, rb, L, R);
    }

    inline void update(int &k, int L, int R, ll val) {
        if (R < L) return;
        update(k, lb, rb, L, R, val);
    }

    inline void set(int &k, int id, ll val) {
        set(k, lb, rb, id, val);
    }

    inline ll query(int k, int L, int R) {
        if (R < L) return 0;
        return query(k, lb, rb, L, R);
    }

    inline ll query(int k, int x) {
        return query(k, lb, rb, x);
    }
};
// endregion