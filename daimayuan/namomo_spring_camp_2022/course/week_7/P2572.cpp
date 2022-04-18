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

// region general
#define ll long long
#define ld long double
#define ull unsigned long long
#define fi first
#define se second

typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
typedef std::tuple<int, int, int> ti3;
typedef std::tuple<ll, ll, ll> tl3;
typedef std::tuple<int, int, int, int> ti4;
typedef std::tuple<ll, ll, ll, ll> tl4;

inline void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
inline void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}
// endregion
// region grid_delta
namespace grid_delta {
    // 上, 右, 下, 左  |  左上, 右上, 右下, 左下
    const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
}
// endregion

using namespace std;
using namespace grid_delta;

const int N = 1e5 + 10;

// region 区修线段树
template<class Info, class Tag, int SZ,
        class Merge = std::plus<Info>>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)

    const Merge merge;
    int lb, rb, rt, mem;
    Info info[SZ * 4];
    Tag tag[SZ * 4];

    Seg() : merge(Merge()) {
        init(1, SZ);
    }

    void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        info[0] = Info();
        tag[0] = Tag();
    }

    int new_node() {
        int id = ++mem;
        info[id] = Info();
        tag[id] = Tag();
        return id;
    }

    void pull(int k) {
        info[k].set(merge(info[ls(k)], info[rs(k)]));
    }

    void apply(int k, ll sz, const Tag &v) {
        info[k].apply(sz, v);
        tag[k].apply(v);
    }

    void push(int k, int s, int e) {
        if (tag[k].check()) {
            ll len = e - s + 1;
            ll lsz = len - len / 2, rsz = len / 2;
            if (!ls(k)) ls(k) = new_node();
            if (!rs(k)) rs(k) = new_node();
            apply(ls(k), lsz, tag[k]);
            apply(rs(k), rsz, tag[k]);
            tag[k] = Tag();
        }
    }

    void upd(int &k, int s, int e, int L, int R, const Tag &v) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            apply(k, e - s + 1, v);
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
        return merge(qr(ls(k), s, mid, L, R), qr(rs(k), mid + 1, e, L, R));
    }

    int qr_kth(int k, int s, int e, ll x) {
        if (s == e) return s;

        if (x <= info[ls(k)].sum) return qr_kth(ls(k), s, mid, x);
        else return qr_kth(rs(k), mid + 1, e, x - info[ls(k)].sum);
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

    int qr_kth(ll x) {
        return qr_kth(rt, lb, rb, x);
    }
};
// endregion

// region 区间求和
struct Tag {
    ll x, y;
    Tag(ll x = -1, ll y = 0) : x(x), y(y) {}

    bool check() const {
        return x != -1 || y != 0;
    }

    void apply(const Tag &a) {
        if (!a.check()) return;
        if (a.x != -1) {
            x = a.x, y = 0;
        } else {
            if (x != -1) x ^= 1;
            else y ^= 1;
        }
    }
};

struct Info {
    int lson, rson;
    ll cnt, c0, c1, l0, l1, r0, r1, lx0, lx1;
    Info(ll cnt = 0, ll c0 = 0, ll c1 = 0, ll l0 = 0, ll l1 = 0, ll r0 = 0, ll r1 = 0, ll lx0 = 0, ll lx1 = 0) :
            lson(0), rson(0), cnt(0), lx0(lx0), lx1(lx1), c0(c0), l0(l0), r0(r0), c1(c1), l1(l1), r1(r1) {}

    void apply(ll sz, const Tag &a) {
        if (!a.check()) return;
        if (a.x != -1) {
            if (a.x) {
                c1 = l1 = r1 = lx1 = cnt;
                c0 = l0 = r0 = lx0 = 0;
            } else {
                c1 = l1 = r1 = lx1 = 0;
                c0 = l0 = r0 = lx0 = cnt;
            }
        } else {
            swap(c0, c1);
            swap(l0, l1);
            swap(r0, r1);
            swap(lx0, lx1);
        }
    }

    friend Info operator+(const Info &a, const Info &b) {
        Info res;
        res.cnt = a.cnt + b.cnt;
        res.c0 = a.c0 + b.c0;
        res.c1 = a.c1 + b.c1;
        res.l0 = a.l0;
        if (a.cnt == a.l0) res.l0 = a.cnt + b.l0;
        res.l1 = a.l1;
        if (a.cnt == a.l1) res.l1 = a.cnt + b.l1;
        res.r0 = b.r0;
        if (b.cnt == b.r0) res.r0 = b.cnt + a.r0;
        res.r1 = b.r1;
        if (b.cnt == b.r1) res.r1 = b.cnt + a.r1;
        res.lx0 = max({a.lx0, b.lx0, a.r0 + b.l0});
        res.lx1 = max({a.lx1, b.lx1, a.r1 + b.l1});
        return res;
    }

    void set(const Info &a) {
        int _lson = lson, _rson = rson;
        *this = a;
        lson = _lson, rson = _rson;
    }
};
// endregion

int n, q;
int a[N];

Seg<Info, Tag, N> seg;

void solve() {
    seg.init(1, n);
    for (int i = 1; i <= n; i++) {
        Info v = Info();
        v.cnt = 1;
        v.c0 = v.l0 = v.r0 = v.lx0 = a[i] == 0;
        v.c1 = v.l1 = v.r1 = v.lx1 = a[i] == 1;
        seg.set(i, v);
    }


    for (int i = 1; i <= q; i++) {
        int op, x, y;
        cin >> op >> x >> y;
        x++, y++;
        if (op == 0) {
            seg.upd(x, y, {0, 0});
        }
        if (op == 1) {
            seg.upd(x, y, {1, 0});
        }
        if (op == 2) {
            seg.upd(x, y, {-1, 1});
        }
        if (op == 3) {
            ll c1 = seg.qr(x, y).c1;
            cout << c1 << "\n";
        }
        if (op == 4) {
            ll lx1 = seg.qr(x, y).lx1;
            cout << lx1 << "\n";
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
    int T = 1;
//    cin >> T;
    while (T--) {
        cin >> n >> q;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}