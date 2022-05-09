// region 单点修改线段树
template<class Info, class Tag, int SZ,
        class Plus = std::plus<Info>>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)

    const Plus plus;
    int lb, rb, rt, mem;
    Info info[SZ * 4];

    Seg() : plus(Plus()) {}

    void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        info[0] = Info();
    }

    int new_node() {
        int id = ++mem;
        assert(id < SZ * 4);
        info[id] = Info();
        return id;
    }

    void pull(int k) {
        info[k].set(plus(info[ls(k)], info[rs(k)]));
    }

    void apply(int k, int s, int e, const Tag &v) {
        info[k].apply(s, e, v);
    }

    void upd(int &k, int s, int e, int id, const Tag &v) {
        if (!k) k = new_node();

        if (s == e) {
            apply(k, s, e, v);
            return;
        }

        if (id <= mid) upd(ls(k), s, mid, id, v);
        if (id >= mid + 1) upd(rs(k), mid + 1, e, id, v);
        pull(k);
    }

    void set(int &k, int s, int e, int id, const Info &v) {
        if (!k) k = new_node();

        if (s == e) {
            info[k].set(v);
            return;
        }

        if (id <= mid) set(ls(k), s, mid, id, v);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, v);
        pull(k);
    }

    Info qr(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return info[k];

        if (R <= mid) return qr(ls(k), s, mid, L, R);
        if (L >= mid + 1) return qr(rs(k), mid + 1, e, L, R);
        return plus(qr(ls(k), s, mid, L, R), qr(rs(k), mid + 1, e, L, R));
    }

    int kth(int k, int s, int e, ll x) {
        if (s == e) return s;

        if (x <= info[ls(k)].sum) return kth(ls(k), s, mid, x);
        else return kth(rs(k), mid + 1, e, x - info[ls(k)].sum);
    }

    void upd(int id, const Tag &v) {
        upd(rt, lb, rb, id, v);
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

    Tag(ll x = 0) : x(x) {}

    bool check() const {
        return x != 0;
    }

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        x += a.x;
    }
};

struct Info {
    int lson, rson;
    ll sum;

    Info(ll sum = 0) : lson(0), rson(0), sum(sum) {}

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        sum += (e - s + 1) * a.x;
    }

    friend Info operator+(const Info &a, const Info &b) {
        return a.sum + b.sum;
    }

    void set(const Info &a) {
        sum = a.sum;
    }
};
// endregion

// region 区间最大值
struct Tag {
    ll x;

    Tag(ll x = 0) : x(x) {}

    bool check() const {
        return x != 0;
    }

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        x = max(x, a.x);
    }
};

struct Info {
    int lson, rson;
    ll sum;

    Info(ll sum = 0) : lson(0), rson(0), sum(sum) {}

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        sum = max(sum, a.x);
    }

    friend Info operator+(const Info &a, const Info &b) {
        return max(a.sum, b.sum);
    }

    void set(const Info &a) {
        sum = a.sum;
    }
};
// endregion

// region 区间最小值
struct Tag {
    ll x;

    Tag(ll x = 1e9) : x(x) {}

    bool check() const {
        return x != 1e9;
    }

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        x = min(x, a.x);
    }
};

struct Info {
    int lson, rson;
    ll sum;

    Info(ll sum = 1e9) : lson(0), rson(0), sum(sum) {}

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        sum = min(sum, a.x);
    }

    friend Info operator+(const Info &a, const Info &b) {
        return min(a.sum, b.sum);
    }

    void set(const Info &a) {
        sum = a.sum;
    }
};
// endregion

// region 区修, 维护最大值
struct Tag {
    ll x;

    Tag(ll x = 0) : x(x) {}

    bool check() const {
        return x != 0;
    }

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        x += a.x;
    }
};

struct Info {
    int lson, rson;
    ll sum, mx;

    Info(ll sum = 0, ll mx = 0) : lson(0), rson(0), sum(sum), mx(mx) {}

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        sum += (e - s + 1) * a.x;
        mx += a.x;
    }

    friend Info operator+(const Info &a, const Info &b) {
        return {a.sum + b.sum, max(a.mx, b.mx)};
    }

    void set(const Info &a) {
        sum = a.sum;
        mx = a.mx;
    }
};
// endregion

// region 区修, 维护最小值
struct Tag {
    ll x;

    Tag(ll x = 0) : x(x) {}

    bool check() const {
        return x != 0;
    }

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        x += a.x;
    }
};

struct Info {
    int lson, rson;
    ll sum, mi;

    Info(ll sum = 0, ll mi = 0) : lson(0), rson(0), sum(sum), mi(mi) {}

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        sum += (e - s + 1) * a.x;
        mi += a.x;
    }

    friend Info operator+(const Info &a, const Info &b) {
        return {a.sum + b.sum, min(a.mi, b.mi)};
    }

    void set(const Info &a) {
        sum = a.sum;
        mi = a.mi;
    }
};
// endregion

// region 扫描线线段树
vector <ll> lsh;

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

    Seg() {
        init(1, SZ);
    }

    void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        tr[0].lson = tr[0].rson = 0;
        tr[0].sum = tr[0].v = 0;
    }

    void init(int L, int R, ll val) {
        init(L, R);
        for (int i = L; i <= R; i++) set(i, val);
    }

    int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        tr[id].sum = tr[id].v = 0;
        return id;
    }

    void pull(int k, int s, int e) {
        if (tr[k].sum) tr[k].v = lsh[e + 1] - lsh[s];
        else if (s != e) tr[k].v = tr[ls(k)].v + tr[rs(k)].v;
        else tr[k].v = 0;
    }

    void add(int &k, int s, int e, int L, int R, ll val) {
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

    void set(int &k, int s, int e, int id, ll val) {
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

    ll query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k].v;

        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        return query(ls(k), s, mid, L, R) + query(rs(k), mid + 1, e, L, R);
    }

    void add(int L, int R, ll val) {
        if (R < L) return;
        add(rt, lb, rb, L, R, val);
    }

    void set(int id, ll val) {
        set(rt, lb, rb, id, val);
    }

    ll query(int L, int R) {
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

    Seg() {
        mem = 0, lb = 1, rb = SZ;
    }

    void init(int L = 1, int R = SZ, int _cnt = 0) {
        lb = L, rb = R, cnt = _cnt;
    }

    void merge(int &x, int y) {
        if (!x || !y) {
            x |= y;
            return;
        }

        tr[x].sum += tr[y].sum;
        tr[x].lz += tr[y].lz;
        merge(ls(x), ls(y));
        merge(rs(x), rs(y));
    }

    int split(int &k, int s, int e, int L, int R) {
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

    int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        return id;
    }

    void pull(int k) {
        tr[k].sum = tr[ls(k)].sum + tr[rs(k)].sum;
    }

    void push(int k, int s, int e) {
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

    void update(int &k, int s, int e, int L, int R, ll val) {
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

    void set(int &k, int s, int e, int id, ll val) {
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

    ll query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k].sum;

        push(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        return query(ls(k), s, mid, L, R) + query(rs(k), mid + 1, e, L, R);
    }

    ll query(int k, int s, int e, int x) {
        if (s == e) return s;
        push(k, s, e);
        if (x <= tr[ls(k)].sum) return query(ls(k), s, mid, x);
        else return query(rs(k), mid + 1, e, x - tr[ls(k)].sum);
    }

    int split(int &k, int L, int R) {
        if (R < L) return -1;
        return split(k, lb, rb, L, R);
    }

    void update(int &k, int L, int R, ll val) {
        if (R < L) return;
        update(k, lb, rb, L, R, val);
    }

    void set(int &k, int id, ll val) {
        set(k, lb, rb, id, val);
    }

    ll query(int k, int L, int R) {
        if (R < L) return 0;
        return query(k, lb, rb, L, R);
    }

    ll query(int k, int x) {
        return query(k, lb, rb, x);
    }
};
// endregion