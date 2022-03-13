// region 普通线段树
template<int SZ>
struct Seg {
#define mid (left + right >> 1)
#define ls (k << 1)
#define rs ((k << 1) + 1)

    const ll MOD = 1e9 + 7;

    struct Node {
        int left, right;
        ll sum, lz;
    };

    ll vt[SZ + 1];
    Node tr[SZ * 4];

    inline void push_up(int k) {
        tr[k].sum = (tr[ls].sum + tr[rs].sum) % MOD;
    }

    inline void push_down(int k) {
        ll lsz = tr[ls].right - tr[ls].left + 1;
        ll rsz = tr[rs].right - tr[rs].left + 1;
        if (tr[k].lz) {
            tr[ls].sum = (tr[ls].sum + lsz * tr[k].lz % MOD) % MOD;
            tr[rs].sum = (tr[rs].sum + rsz * tr[k].lz % MOD) % MOD;
            tr[ls].lz = (tr[ls].lz + tr[k].lz) % MOD;
            tr[rs].lz = (tr[rs].lz + tr[k].lz) % MOD;
            tr[k].lz = 0;
        }
    }

    inline void build(int k, int left, int right) {
        tr[k].left = left, tr[k].right = right;
        tr[k].sum = tr[k].lz = 0;

        if (left == right) {
            tr[k].sum = vt[left];
            return;
        }
        build(ls, left, mid);
        build(rs, mid + 1, right);
        push_up(k);
    }

    inline void update(int k, int L, int R, ll val) {
        int left = tr[k].left, right = tr[k].right;

        if (right < L || left > R) return;
        if (L <= left && right <= R) {
            tr[k].sum = (tr[k].sum + (right - left + 1) * val % MOD) % MOD;
            tr[k].lz = (tr[k].lz + val) % MOD;
            return;
        }

        push_down(k);
        update(ls, L, R, val);
        update(rs, L, R, val);
        push_up(k);
    }

    inline ll query(int k, int L, int R) {
        int left = tr[k].left, right = tr[k].right;

        if (right < L || left > R) return 0;
        if (L <= left && right <= R) return tr[k].sum;

        push_down(k);
        return (query(ls, L, R) + query(rs, L, R)) % MOD;
    }

    inline void build(int L, int R) {
        return build(1, L, R);
    }

    inline void update(int L, int R, ll val) {
        update(1, L, R, val);
    }

    inline ll query(int L, int R) {
        return query(1, L, R);
    }
};
// endregion

// region 区间最小值线段树
template<int SZ>
struct Seg {
#define mid (left + right >> 1)
#define ls (k << 1)
#define rs ((k << 1) + 1)

    struct Node {
        int left, right;
        ll sum, lz, mi;
    };

    ll vt[SZ + 1];
    Node tr[SZ * 4];

    inline void push_up(int k) {
        tr[k].sum = tr[ls].sum + tr[rs].sum;
        tr[k].mi = min(tr[ls].mi, tr[rs].mi);
    }

    inline void push_down(int k) {
        ll lsz = tr[ls].right - tr[ls].left + 1;
        ll rsz = tr[rs].right - tr[rs].left + 1;
        if (tr[k].lz) {
            tr[ls].sum = tr[ls].sum + lsz * tr[k].lz;
            tr[rs].sum = tr[rs].sum + rsz * tr[k].lz;
            tr[ls].lz = tr[ls].lz + tr[k].lz;
            tr[rs].lz = tr[rs].lz + tr[k].lz;
            tr[k].lz = 0;
        }
    }

    inline void build(int k, int left, int right) {
        tr[k].left = left, tr[k].right = right;
        tr[k].sum = tr[k].mi = tr[k].lz = 0;

        if (left == right) {
            tr[k].sum = tr[k].mi = vt[left];
            return;
        }
        build(ls, left, mid);
        build(rs, mid + 1, right);
        push_up(k);
    }

    inline void update(int k, int L, int R, ll val) {
        int left = tr[k].left, right = tr[k].right;

        if (right < L || left > R) return;
        if (L <= left && right <= R) {
            tr[k].sum = tr[k].sum + (right - left + 1) * val;
            tr[k].lz = tr[k].lz + val;
            tr[k].mi = tr[k].mi + val;
            return;
        }

        push_down(k);
        update(ls, L, R, val);
        update(rs, L, R, val);
        push_up(k);
    }

    inline void modify(int k, int id, ll val) {
        int left = tr[k].left, right = tr[k].right;

        if (right < id || left > id) return;
        if (left == right) {
            tr[k].sum = tr[k].mx = min(tr[k].mx, val);
            return;
        }
        modify(ls, id, val);
        modify(rs, id, val);
        push_up(k);
    }

    inline ll query(int k, int L, int R) {
        int left = tr[k].left, right = tr[k].right;

        if (right < L || left > R) return 1e18;
        if (L <= left && right <= R) return tr[k].mi;

        push_down(k);
        return min(query(ls, L, R), query(rs, L, R));
    }

    inline void build(int L, int R) {
        return build(1, L, R);
    }

    inline void update(int L, int R, ll val) {
        update(1, L, R, val);
    }

    inline void modify(int id, ll val) {
        modify(1, id, val);
    }

    inline ll query(int L, int R) {
        return query(1, L, R);
    }
};
// endregion

// region 区间最大值线段树
template<int SZ>
struct Seg {
#define mid (left + right >> 1)
#define ls (k << 1)
#define rs ((k << 1) + 1)

    struct Node {
        int left, right;
        ll sum, lz, mx;
    };

    ll vt[SZ + 1];
    Node tr[SZ * 4];

    inline void push_up(int k) {
        tr[k].sum = tr[ls].sum + tr[rs].sum;
        tr[k].mx = max(tr[ls].mx, tr[rs].mx);
    }

    inline void push_down(int k) {
        ll lsz = tr[ls].right - tr[ls].left + 1;
        ll rsz = tr[rs].right - tr[rs].left + 1;
        if (tr[k].lz) {
            tr[ls].sum = tr[ls].sum + lsz * tr[k].lz;
            tr[rs].sum = tr[rs].sum + rsz * tr[k].lz;
            tr[ls].lz = tr[ls].lz + tr[k].lz;
            tr[rs].lz = tr[rs].lz + tr[k].lz;
            tr[k].lz = 0;
        }
    }

    inline void build(int k, int left, int right) {
        tr[k].left = left, tr[k].right = right;
        tr[k].sum = tr[k].mx = tr[k].lz = 0;

        if (left == right) {
            tr[k].sum = tr[k].mx = vt[left];
            return;
        }
        build(ls, left, mid);
        build(rs, mid + 1, right);
        push_up(k);
    }

    inline void update(int k, int L, int R, ll val) {
        int left = tr[k].left, right = tr[k].right;

        if (right < L || left > R) return;
        if (L <= left && right <= R) {
            tr[k].sum = tr[k].sum + (right - left + 1) * val;
            tr[k].lz = tr[k].lz + val;
            tr[k].mx = tr[k].mx + val;
            return;
        }

        push_down(k);
        update(ls, L, R, val);
        update(rs, L, R, val);
        push_up(k);
    }

    inline void modify(int k, int id, ll val) {
        int left = tr[k].left, right = tr[k].right;

        if (right < id || left > id) return;
        if (left == right) {
            tr[k].sum = tr[k].mx = max(tr[k].mx, val);
            return;
        }
        modify(ls, id, val);
        modify(rs, id, val);
        push_up(k);
    }

    inline ll query(int k, int L, int R) {
        int left = tr[k].left, right = tr[k].right;

        if (right < L || left > R) return 0;
        if (L <= left && right <= R) return tr[k].mx;

        push_down(k);
        return max(query(ls, L, R), query(rs, L, R));
    }

    inline void build(int L, int R) {
        return build(1, L, R);
    }

    inline void update(int L, int R, ll val) {
        update(1, L, R, val);
    }

    inline void modify(int id, ll val) {
        modify(1, id, val);
    }

    inline ll query(int L, int R) {
        return query(1, L, R);
    }
};
// endregion

// region 线段树维护矩阵
template<int SZ>
struct Mat {
    int r, c;
    ll a[SZ + 1][SZ + 1];

    inline Mat(int r = 0, int c = 0) : r(r), c(c) {
        memset(a, 0, sizeof a);
    }

    inline Mat operator-(const Mat &T) const {
        Mat res(r, c);
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                res.a[i][j] = (a[i][j] - T.a[i][j]) % MOD;
            }
        }
        return res;
    }

    inline Mat operator+(const Mat &T) const {
        Mat res(r, c);
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                res.a[i][j] = (a[i][j] + T.a[i][j]) % MOD;
            }
        }
        return res;
    }

    inline Mat operator*(const Mat &T) const {
        Mat res(r, T.c);
        for (int i = 1; i <= res.r; i++) {
            for (int j = 1; j <= T.c; j++) {
                for (int k = 1; k <= c; k++) {
                    res.a[i][j] = (res.a[i][j] + a[i][k] * T.a[k][j] % MOD) % MOD;
                }
            }
        }
        return res;
    }

    inline Mat operator*(ll x) const {
        Mat res(r, c);
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                res.a[i][j] = (a[i][j] * x) % MOD;
            }
        }
        return res;
    }

    inline Mat operator^(ll x) const {
        Mat res(r, c), bas(r, c);
        for (int i = 1; i <= r; i++) res.a[i][i] = 1;
        memcpy(bas.a, a, sizeof a);

        while (x) {
            if (x & 1) res = res * bas;
            bas = bas * bas;
            x >>= 1;
        }
        return res;
    }

    inline bool operator==(const Mat &T) const {
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                if (a[i][j] != T.a[i][j]) return false;
            }
        }
        return true;
    }

    inline void print() const {
        for (int i = 1; i <= r; i++) {
            for (int j = 1; j <= c; j++) {
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

template<int SZ>
struct Seg {
#define mid (left + right >> 1)
#define ls (k << 1)
#define rs ((k << 1) + 1)

    struct Node {
        int left, right;
        Mat<4> sum = Mat<4>(1, 4);
        Mat<4> lz = Mat<4>(4, 4);
    };

    Node tr[SZ * 4];
    Mat<4> E;

    inline void push_up(int k) {
        for (int j = 1; j <= 4; j++) {
            tr[k].sum.a[1][j] = (tr[ls].sum.a[1][j] + tr[rs].sum.a[1][j]) % MOD;
        }
    }

    inline void push_down(int k) {
        if (!(tr[k].lz == E)) {
            tr[ls].sum = tr[ls].sum * tr[k].lz;
            tr[ls].lz = tr[ls].lz * tr[k].lz;
            tr[rs].sum = tr[rs].sum * tr[k].lz;
            tr[rs].lz = tr[rs].lz * tr[k].lz;
            tr[k].lz = E;
        }
    }

    inline void build(int k, int left, int right) {
        tr[k].left = left, tr[k].right = right;
        tr[k].lz = E;

        if (left == right) {
            tr[k].sum.a[1][4] = 1;
            return;
        }
        build(ls, left, mid);
        build(rs, mid + 1, right);
        tr[k].sum.a[1][4] = tr[ls].sum.a[1][4] + tr[rs].sum.a[1][4];
    }

    inline void update(int k, int L, int R, Mat<4> &val) {
        int left = tr[k].left, right = tr[k].right;

        if (right < L || left > R) return;
        if (L <= left && right <= R) {
            tr[k].sum = tr[k].sum * val;
            tr[k].lz = tr[k].lz * val;
            return;
        }

        push_down(k);
        update(ls, L, R, val);
        update(rs, L, R, val);
        push_up(k);
    }

    inline ll query(int k, int L, int R, int x) {
        int left = tr[k].left, right = tr[k].right;

        if (right < L || left > R) return 0;
        if (L <= left && right <= R) return tr[k].sum.a[1][x];

        push_down(k);
        return (query(ls, L, R, x) + query(rs, L, R, x)) % MOD;
    }
}
// endregion

// region 动态开点普通线段树
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

    int lb, rb, rt;
    Node tr[SZ * 4];
    int nw;

    inline Seg() {
        lb = 1, rb = SZ;
    }

    inline void init(int L = 1, int R = SZ, int val = 0) {
        lb = L, rb = R;
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++nw;
        return id;
    }

    inline void push_up(int k) {
        tr[k].sum = tr[ls(k)].sum + tr[rs(k)].sum;
    }

    inline void push_down(int k, int s, int e) {
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
            tr[k].sum = tr[k].sum + (e - s + 1) * val;
            tr[k].lz = tr[k].lz + val;
            return;
        }

        push_down(k, s, e);
        if (L <= mid) update(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) update(rs(k), mid + 1, e, L, R, val);
        push_up(k);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = val;
            return;
        }

        push_down(k, s, e);
        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        push_up(k);
    }

    inline ll query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k].sum;

        push_down(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        return query(ls(k), s, mid, L, R) + query(rs(k), mid + 1, e, L, R);
    }

    inline ll query_k(int k, int s, int e, int x) {
        if (s == e) return s;

        if (x <= tr[ls(k)].sum) return query_k(ls(k), s, mid, x);
        else return query_k(rs(k), mid + 1, e, x - tr[ls(k)].sum);
    }

    inline void update(int L, int R, ll val) {
        if (R < L) return;
        update(rt, lb, rb, L, R, val);
    }

    inline void set(int id, ll val) {
        set(rt, lb, rb, id, val);
    }

    inline ll query(int L, int R) {
        if (R < L) return 0;
        return query(rt, lb, rb, L, R);
    }

    inline ll query_k(int x) {
        return query_k(rt, lb, rb, x);
    }
};
// endregion

// region 动态开点最大值线段树
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        ll sum, lz, mx;
    };

    int lb, rb, rt;
    Node tr[SZ * 4];
    int nw;

    inline Seg() {
        lb = 1, rb = SZ;
    }

    inline void init(int L = 1, int R = SZ, int val = 0) {
        lb = L, rb = R;
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++nw;
        tr[id].sum = tr[id].lz = tr[id].mx = 0;
        return id;
    }

    inline void push_up(int k) {
        tr[k].sum = tr[ls(k)].sum + tr[rs(k)].sum;
        tr[k].mx = max(tr[ls(k)].mx, tr[rs(k)].mx);
    }

    inline void push_down(int k, int s, int e) {
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
            tr[k].sum = tr[k].sum + (e - s + 1) * val;
            tr[k].mx = tr[k].mx + val;
            tr[k].lz = tr[k].lz + val;
            return;
        }

        push_down(k, s, e);
        if (L <= mid) update(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) update(rs(k), mid + 1, e, L, R, val);
        push_up(k);
    }

    inline void modify(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = tr[k].mx = max(tr[k].mx, val);
            return;
        }

        push_down(k, s, e);
        if (id <= mid) modify(ls(k), s, mid, id, val);
        if (id >= mid + 1) modify(rs(k), mid + 1, e, id, val);
        push_up(k);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = tr[k].mx = val;
            return;
        }

        push_down(k, s, e);
        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        push_up(k);
    }

    inline ll query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k].mx;

        push_down(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        return max(query(ls(k), s, mid, L, R), query(rs(k), mid + 1, e, L, R));
    }

    inline void update(int L, int R, ll val) {
        if (R < L) return;
        update(rt, lb, rb, L, R, val);
    }

    inline void modify(int id, ll val) {
        modify(rt, lb, rb, id, val);
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

// region 动态开点最小值线段树
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        ll sum, lz, mi;
    };

    int lb, rb, rt;
    Node tr[SZ * 4];
    int nw;

    inline Seg() {
        lb = 1, rb = SZ;
    }

    inline void init(int L = 1, int R = SZ, int val = 0) {
        lb = L, rb = R;
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++nw;
        tr[id].sum = tr[id].lz = tr[id].mi = 0;
        return id;
    }

    inline void push_up(int k) {
        tr[k].sum = tr[ls(k)].sum + tr[rs(k)].sum;
        tr[k].mi = min(tr[ls(k)].mi, tr[rs(k)].mi);
    }

    inline void push_down(int k, int s, int e) {
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
            tr[k].sum = tr[k].sum + (e - s + 1) * val;
            tr[k].mi = tr[k].mi + val;
            tr[k].lz = tr[k].lz + val;
            return;
        }

        push_down(k, s, e);
        if (L <= mid) update(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) update(rs(k), mid + 1, e, L, R, val);
        push_up(k);
    }

    inline void modify(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = tr[k].mi = min(tr[k].mi, val);
            return;
        }

        push_down(k, s, e);
        if (id <= mid) modify(ls(k), s, mid, id, val);
        if (id >= mid + 1) modify(rs(k), mid + 1, e, id, val);
        push_up(k);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = tr[k].mi = val;
            return;
        }

        push_down(k, s, e);
        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        push_up(k);
    }

    inline ll query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k].mi;

        push_down(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        return min(query(ls(k), s, mid, L, R), query(rs(k), mid + 1, e, L, R));
    }

    inline void update(int L, int R, ll val) {
        if (R < L) return;
        update(rt, lb, rb, L, R, val);
    }

    inline void modify(int id, ll val) {
        modify(rt, lb, rb, id, val);
    }

    inline void set(int id, ll val) {
        set(rt, lb, rb, id, val);
    }

    inline ll query(int L, int R) {
        if (R < L) return 1e18;
        return query(rt, lb, rb, L, R);
    }
};
// endregion

// region 普通线段树分裂
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

    int lb, rb;
    Node tr[SZ * 40];
    int nw;
    int root[SZ + 1], cnt;

    inline Seg() {
        lb = 1, rb = SZ;
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
            push_up(k), push_up(id);
        }
        return id;
    }

    inline int new_node() {
        int id = ++nw;
        return id;
    }

    inline void push_up(int k) {
        tr[k].sum = tr[ls(k)].sum + tr[rs(k)].sum;
    }

    inline void push_down(int k, int s, int e) {
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

        push_down(k, s, e);
        if (L <= mid) update(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) update(rs(k), mid + 1, e, L, R, val);
        push_up(k);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = val;
            return;
        }

        push_down(k, s, e);
        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        push_up(k);
    }

    inline ll query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k].sum;

        push_down(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        return query(ls(k), s, mid, L, R) + query(rs(k), mid + 1, e, L, R);
    }

    inline ll query(int k, int s, int e, int x) {
        if (s == e) return s;
        push_down(k, s, e);
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