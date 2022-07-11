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

// region 区修, 维护最大值
struct Tag {
    ll x;
    Tag(ll x = 0) : x(x) {}

    bool check() const {
        return x != 0;
    }

    void apply(const Tag &a) {
        if (!a.check()) return;
        x += a.x;
    }
};

struct Info {
    int lson, rson;
    ll sum, mx, mx_id;
    Info(ll sum = 0, ll mx = 0, ll mx_id = 0) : lson(0), rson(0), sum(sum), mx(mx), mx_id(mx_id) {}

    void apply(ll sz, const Tag &a) {
        if (!a.check()) return;
        sum += sz * a.x;
        mx += a.x;
    }

    friend Info operator+(const Info &a, const Info &b) {
        ll _mx, _mx_id;
        _mx = max(a.mx, b.mx);
        if (a.mx > b.mx) _mx_id = a.mx_id;
        else _mx_id = b.mx_id;
        return {a.sum + b.sum, _mx, _mx_id};
    }

    void set(const Info &a) {
        sum = a.sum;
        mx = a.mx;
        mx_id = a.mx_id;
    }
};
// endregion

const int N = 1e5 + 10;

int n, Q;
int a[N];

Seg<Info, Tag, N> seg;

void solve() {
    seg.init(1, n);
    for (int i = 1; i <= n; i++) seg.set(i, {a[i], a[i], i});

    while (Q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int L, R;
            cin >> L >> R;

            auto t = seg.qr(L, R);
            cout << t.sum << "\n";
        } else if (op == 2) {
            int L, R, x;
            cin >> L >> R >> x;

            while (1) {
                auto t = seg.qr(L, R);
                if (t.mx < x) break;

                int id = t.mx_id;
                int v = t.mx % x;
                seg.set(id, {v, v, id});
            }
        } else {
            int id, x;
            cin >> id >> x;

            seg.set(id, {x, x, id});
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
        cin >> n >> Q;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}