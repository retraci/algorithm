// region 普通线段树
template<int SZ>
struct Seg {
#define mid (left + right >> 1)
#define ls (node << 1)
#define rs ((node << 1) + 1)

    const ll MOD = 1e9 + 7;

    struct Node {
        int left, right;
        ll sum, lz;
    };

    ll vt[SZ + 1];
    Node tr[SZ * 4];

    inline void push_up(int node) {
        tr[node].sum = (tr[ls].sum + tr[rs].sum) % MOD;
    }

    inline void push_down(int node) {
        ll lsz = tr[ls].right - tr[ls].left + 1;
        ll rsz = tr[rs].right - tr[rs].left + 1;
        if (tr[node].lz) {
            tr[ls].sum = (tr[ls].sum + lsz * tr[node].lz % MOD) % MOD;
            tr[rs].sum = (tr[rs].sum + rsz * tr[node].lz % MOD) % MOD;
            tr[ls].lz = (tr[ls].lz + tr[node].lz) % MOD;
            tr[rs].lz = (tr[rs].lz + tr[node].lz) % MOD;
            tr[node].lz = 0;
        }
    }

    inline void build(int node, int left, int right) {
        tr[node].left = left, tr[node].right = right;
        tr[node].sum = tr[node].lz = 0;

        if (left == right) {
            tr[node].sum = vt[left];
            return;
        }
        build(ls, left, mid);
        build(rs, mid + 1, right);
        push_up(node);
    }

    inline void update(int node, int L, int R, ll val) {
        int left = tr[node].left, right = tr[node].right;

        if (right < L || left > R) return;
        if (L <= left && right <= R) {
            tr[node].sum = (tr[node].sum + (R - L + 1) * val % MOD) % MOD;
            tr[node].lz = (tr[node].lz + val) % MOD;
            return;
        }

        push_down(node);
        update(ls, L, R, val);
        update(rs, L, R, val);
        push_up(node);
    }

    inline ll query(int node, int L, int R) {
        int left = tr[node].left, right = tr[node].right;

        if (right < L || left > R) return 0;
        if (L <= left && right <= R) return tr[node].sum;

        push_down(node);
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
#define ls (node << 1)
#define rs ((node << 1) + 1)

    struct Node {
        int left, right;
        ll sum, lz, mi;
    };

    ll vt[SZ + 1];
    Node tr[SZ * 4];

    inline void push_up(int node) {
        tr[node].sum = tr[ls].sum + tr[rs].sum;
        tr[node].mi = min(tr[ls].mi, tr[rs].mi);
    }

    inline void push_down(int node) {
        ll lsz = tr[ls].right - tr[ls].left + 1;
        ll rsz = tr[rs].right - tr[rs].left + 1;
        if (tr[node].lz) {
            tr[ls].sum = tr[ls].sum + lsz * tr[node].lz;
            tr[rs].sum = tr[rs].sum + rsz * tr[node].lz;
            tr[ls].lz = tr[ls].lz + tr[node].lz;
            tr[rs].lz = tr[rs].lz + tr[node].lz;
            tr[node].lz = 0;
        }
    }

    inline void build(int node, int left, int right) {
        tr[node].left = left, tr[node].right = right;
        tr[node].sum = tr[node].mi = tr[node].lz = 0;

        if (left == right) {
            tr[node].sum = tr[node].mi = vt[left];
            return;
        }
        build(ls, left, mid);
        build(rs, mid + 1, right);
        push_up(node);
    }

    inline void update(int node, int L, int R, ll val) {
        int left = tr[node].left, right = tr[node].right;

        if (right < L || left > R) return;
        if (L <= left && right <= R) {
            tr[node].sum = tr[node].sum + (R - L + 1) * val;
            tr[node].lz = tr[node].lz + val;
            tr[node].mi = tr[node].mi + val;
            return;
        }

        push_down(node);
        update(ls, L, R, val);
        update(rs, L, R, val);
        push_up(node);
    }

    inline ll query(int node, int L, int R) {
        int left = tr[node].left, right = tr[node].right;

        if (right < L || left > R) return 1e18;
        if (L <= left && right <= R) return tr[node].mi;

        push_down(node);
        return min(query(ls, L, R), query(rs, L, R));
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
#define ls (node << 1)
#define rs ((node << 1) + 1)

    struct Node {
        int left, right;
        Mat<4> sum = Mat<4>(1, 4);
        Mat<4> lz = Mat<4>(4, 4);
    };

    Node tr[SZ * 4];
    Mat<4> E;

    inline void push_up(int node) {
        for (int j = 1; j <= 4; j++) {
            tr[node].sum.a[1][j] = (tr[ls].sum.a[1][j] + tr[rs].sum.a[1][j]) % MOD;
        }
    }

    inline void push_down(int node) {
        if (!(tr[node].lz == E)) {
            tr[ls].sum = tr[ls].sum * tr[node].lz;
            tr[ls].lz = tr[ls].lz * tr[node].lz;
            tr[rs].sum = tr[rs].sum * tr[node].lz;
            tr[rs].lz = tr[rs].lz * tr[node].lz;
            tr[node].lz = E;
        }
    }

    inline void build(int node, int left, int right) {
        tr[node].left = left, tr[node].right = right;
        tr[node].lz = E;

        if (left == right) {
            tr[node].sum.a[1][4] = 1;
            return;
        }
        build(ls, left, mid);
        build(rs, mid + 1, right);
        tr[node].sum.a[1][4] = tr[ls].sum.a[1][4] + tr[rs].sum.a[1][4];
    }

    inline void update(int node, int L, int R, Mat<4> &val) {
        int left = tr[node].left, right = tr[node].right;

        if (right < L || left > R) return;
        if (L <= left && right <= R) {
            tr[node].sum = tr[node].sum * val;
            tr[node].lz = tr[node].lz * val;
            return;
        }

        push_down(node);
        update(ls, L, R, val);
        update(rs, L, R, val);
        push_up(node);
    }

    inline ll query(int node, int L, int R, int x) {
        int left = tr[node].left, right = tr[node].right;

        if (right < L || left > R) return 0;
        if (L <= left && right <= R) return tr[node].sum.a[1][x];

        push_down(node);
        return (query(ls, L, R, x) + query(rs, L, R, x)) % MOD;
    }
}
// endregion