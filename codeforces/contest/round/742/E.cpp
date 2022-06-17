#include <bits/stdc++.h>

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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int mod) {
    return mrnd() % mod;
}

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

        if (info[ls(k)].sum >= x) return kth(ls(k), s, mid, x);
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

// region 区间求和
struct Tag {
    int x;

    Tag(int x = 0) : x(x) {}

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
    int llen, rlen, lv, rv, len;

    Info(ll sum = 0, int llen = 0, int rlen = 0, int lv = 0, int rv = 0, int len = 0) : lson(0), rson(0), sum(sum),
    llen(llen), rlen(rlen), lv(lv), rv(rv), len(len) {}

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        lv = rv = a.x;
    }

    friend Info operator+(const Info &a, const Info &b) {
        Info res;
        res.sum = a.sum + b.sum;
        if (a.rv <= b.lv) res.sum += 1LL * a.rlen * b.llen;
        res.lv = a.lv, res.rv = b.rv;
        res.llen = a.llen, res.rlen = b.rlen;
        if (a.llen == a.len && a.rv <= b.lv) res.llen += b.llen;
        if (b.rlen == b.len && a.rv <= b.lv) res.rlen += a.rlen;
        res.len = a.len + b.len;
        return res;
    }

    void set(const Info &a) {
        int _lson = lson, _rson = rson;
        *this = a;
        lson = _lson, rson = _rson;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 2e5 + 10;

int n, q;
int a[N];
Seg<Info, Tag, N> seg;

void solve() {
    seg.init(1, n);
    for (int i = 1; i <= n; i++) {
        Info t;
        t.sum = t.len = t.llen = t.rlen = 1;
        t.lv = t.rv = a[i];
        seg.set(i, t);
    }

    while (q--) {
        int op, x, y;
        cin >> op >> x >> y;

        if (op == 1) {
            seg.upd(x, y);
        } else {
            auto t = seg.qr(x, y);
            cout << t.sum << "\n";
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
        cin >> n >> q;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}