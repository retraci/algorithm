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
        return merge(qr(ls(k), s, mid, L, R), qr(rs(k), mid + 1, e, L, R));
    }

    int qr_kth(int k, int s, int e, ll x) {
        if (s == e) return info[k].mih < x ? s : 0;

        push(k, s, e);
        if (info[rs(k)].mih < x) return qr_kth(rs(k), mid + 1, e, x);
        else return qr_kth(ls(k), s, mid, x);
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
    ll dta, cut;
    Tag(ll dta = 0, ll cut = -1) : dta(dta), cut(cut) {}

    bool check() const {
        return dta != 0 || cut != -1;
    }

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        if (a.cut != -1) *this = a;
        else dta += a.dta;
    }
};

struct Info {
    int lson, rson;
    ll sg, sh, mig, mih;
    Info(ll sg = 0, ll sh = 0, ll mig = 0, ll mih = 0) : lson(0), rson(0), sg(sg), sh(sh), mig(mig), mih(mih) {}

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        if (a.cut != -1) {
            sh = (e - s + 1) * a.cut;
            mih = a.cut;
        }
        sh += sg * a.dta;
        mih += mig * a.dta;
    }

    friend Info operator+(const Info &a, const Info &b) {
        Info res = Info();
        res.sg = a.sg + b.sg;
        res.sh = a.sh + b.sh;
        res.mig = a.mig;
        res.mih = a.mih;
        return res;
    }

    void set(const Info &a) {
        int _l = lson, _r = rson;
        *this = a;
        lson = _l, rson = _r;
    }
};
// endregion

const int N = 1e5 + 10;

int n, m;
ll a[N];
Seg<Info, Tag, N> seg;

void solve() {
    sort(a + 1, a + n + 1);

    seg.init(1, n);
    for (int i = 1; i <= n; i++) {
        Info v = Info();
        v.sg = v.mig = a[i];
        seg.set(i, v);
    }

    ll lst = 0;
    while (m--) {
        ll d, b;
        cin >> d >> b;

        seg.upd(1, n, {(d - lst), -1});
        int id = seg.qr_kth(b);
        ll ans = 0;
        if (id + 1 <= n) {
            auto t = seg.qr(id + 1, n);
            ans = t.sh - (n - id) * b;
            seg.upd(id + 1, n, {0, b});
        }

        lst = d;

        cout << ans << "\n";
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
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}