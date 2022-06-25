// region 可持久化 01trie
int a[N];

template<int N, int SZ, int B>
struct Trie {
    int tr[SZ + 10][2], mx_id[SZ + 10], mem;
    int root[N + 10];

    inline Trie() {
        init();
    }

    inline void init() {
        root[0] = 0, mem = 0;
        tr[0][0] = tr[0][1] = mx_id[0] = 0;
    }

    inline int new_node() {
        int id = ++mem;
        tr[id][0] = tr[id][1] = mx_id[id] = 0;
        return id;
    }

    inline void insert(int id) {
        int k = root[id] = new_node();
        int p = id - 1 >= 0 ? root[id - 1] : 0;
        for (int i = B; i >= 0; i--) {
            int v = a[id] >> i & 1;
            tr[k][v] = new_node();
            if (p) {
                tr[k][v ^ 1] = tr[p][v ^ 1];
                p = tr[p][v];
            }
            mx_id[tr[k][v]] = id;
            k = tr[k][v];
        }
    }

    inline int query(int x, int L, int R) {
        int k = root[R];
        for (int i = B; i >= 0; i--) {
            int v = x >> i & 1;
            if (tr[k][v ^ 1] && mx_id[tr[k][v ^ 1]] >= L) k = tr[k][v ^ 1];
            else k = tr[k][v];
        }

        return x ^ a[mx_id[k]];
    }
};
// endregion

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
    int root[SZ + 10];

    inline Seg() {
        init(1, SZ);
    }

    inline void init(int L, int R) {
        mem = 0, lb = L, rb = R;
        tr[0].lson = tr[0].rson = 0;
        tr[0].sum = 0;
    }

    inline int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        tr[id].sum = 0;
        return id;
    }

    inline void push_up(int k) {
        tr[k].sum = tr[ls(k)].sum + tr[rs(k)].sum;
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

    inline int add(int p, int s, int e, int id, ll val) {
        int k = new_node();
        tr[k] = tr[p];

        if (s == e) {
            tr[k].sum = tr[k].sum + val;
            return k;
        }

        if (id <= mid) ls(k) = add(ls(p), s, mid, id, val);
        if (id >= mid + 1) rs(k) = add(rs(p), mid + 1, e, id, val);
        push_up(k);
        return k;
    }

    inline int set(int p, int s, int e, int id, ll val) {
        int k = new_node();
        tr[k] = tr[p];

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
        return query(ls(k), s, mid, L, R) + query(rs(k), mid + 1, e, L, R);
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

    inline void add(int nv, int pv, int id, ll val) {
        root[nv] = add(root[pv], lb, rb, id, val);
    }

    inline void set(int nv, int pv, int id, ll val) {
        root[nv] = set(root[pv], lb, rb, id, val);
    }

    inline ll query(int v, int L, int R) {
        if (R < L) return 0;
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

// region mex主席树
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        int sum;
    };

    int lb, rb, mem;
    Node tr[32 * SZ];
    int root[SZ + 10];

    inline Seg() {
        init(1, SZ);
    }

    inline void init(int L, int R) {
        mem = 0, lb = L, rb = R;
        tr[0].lson = tr[0].rson = 0;
        tr[0].sum = 0;
    }

    inline int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        tr[id].sum = 0;
        return id;
    }

    inline void push_up(int k) {
        tr[k].sum = min(tr[ls(k)].sum, tr[rs(k)].sum);
    }

    inline int set(int p, int s, int e, int id, int val) {
        int k = new_node();
        tr[k] = tr[p];

        if (s == e) {
            tr[k].sum = val;
            return k;
        }

        if (id <= mid) ls(k) = set(ls(p), s, mid, id, val);
        if (id >= mid + 1) rs(k) = set(rs(p), mid + 1, e, id, val);
        push_up(k);
        return k;
    }

    inline int query(int k, int s, int e, int L) {
        if (s == e) return s;

        if (tr[ls(k)].sum < L) return query(ls(k), s, mid, L);
        else return query(rs(k), mid + 1, e, L);
        return min(query(ls(k), s, mid, L), query(rs(k), mid + 1, e, L));
    }

    inline void set(int nv, int pv, int id, int val) {
        root[nv] = set(root[pv], lb, rb, id, val);
    }

    inline int query(int v, int L) {
        return query(root[v], lb, rb, L);
    }
};
// endregion
