#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <bitset>

// region hash_func
template<typename TT>
struct tuple_hash {
    size_t operator()(TT const &tt) const {
        return std::hash<TT>()(tt);
    }
};

template<class T>
inline void hash_combine(std::size_t &seed, T const &v) {
    seed ^= tuple_hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
struct HashValueImpl {
    void operator()(size_t &seed, Tuple const &tuple) const {
        HashValueImpl<Tuple, Index - 1>{}(seed, tuple);
        hash_combine(seed, std::get<Index>(tuple));
    }
};

template<class Tuple>
struct HashValueImpl<Tuple, 0> {
    void operator()(size_t &seed, Tuple const &tuple) const {
        hash_combine(seed, std::get<0>(tuple));
    }
};

template<typename... TT>
struct tuple_hash<std::tuple<TT...>> {
    size_t operator()(std::tuple<TT...> const &tt) const {
        size_t seed = 0;
        HashValueImpl<std::tuple<TT...>>{}(seed, tt);
        return seed;
    }
};

template<typename T>
inline void hash_val(std::size_t &seed, const T &val) {
    hash_combine(seed, val);
}

template<typename T, typename... Types>
inline void hash_val(std::size_t &seed, const T &val, const Types &... args) {
    hash_combine(seed, val);
    hash_val(seed, args...);
}

template<typename... Types>
inline std::size_t hash_val(const Types &... args) {
    std::size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

struct pair_hash {
    template<class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const {
        return hash_val(p.first, p.second);
    }
};
// endregion
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
// endregion
// region grid_delta
namespace grid_delta {
    // 上, 右, 下, 左  |  左上, 右上, 左下, 右下
    const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
    const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};
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

// region 区修, 维护最小值
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
    ll sum, mi;
    Info(ll sum = 0, ll mi = 0) : lson(0), rson(0), sum(sum), mi(mi) {}

    void apply(ll sz, const Tag &a) {
        if (!a.check()) return;
        sum += sz * a.x;
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

const int N = 1e5 + 10;

int n, m;
ll va[N];
vector<ll> vb[N];
Seg<Info, Tag, 2 * N> seg;

void solve() {
    int K = 0;
    for (int i = 1; i <= m; i++) K += vb[i].size();

    ll vc[m + 1];
    for (int i = 1; i <= m; i++) {
        vc[i] = accumulate(vb[i].begin(), vb[i].end(), 0LL);
    }

    int tt = n + m;
    pll vd[tt + 1];
    for (int i = 1; i <= n; i++) vd[i] = {va[i], 2};
    for (int i = 1; i <= m; i++) {
        ll avg = (vc[i] + vb[i].size() - 1) / vb[i].size();
        vd[n + i] = {avg, 1};
    }
    sort(vd + 1, vd + tt + 1);

    ll suf[tt + 2];
    suf[tt + 1] = 0;
    for (int i = tt; i >= 1; i--) {
        suf[i] = suf[i + 1] + (vd[i].se == 2 ? 1 : -1);
    }

    seg.init(1, tt + 1);
    for (int i = 1; i <= tt + 1; i++) seg.set(i, {suf[i], suf[i]});

    string ans(K, '0');
    int idx = 0;
    for (int i = 1; i <= m; i++) {
        for (int x: vb[i]) {
            ll s = (vc[i] + vb[i].size() - 1) / vb[i].size();
            ll sz = vb[i].size() - 1;
            ll ns = (vc[i] - x + sz - 1) / sz;
            ll id1 = lower_bound(vd + 1, vd + 1 + tt, (pll) {s, 1}) - vd;
            ll id2 = lower_bound(vd + 1, vd + 1 + tt, (pll) {ns, 1}) - vd;

            if (id1 < id2) {
                seg.upd(id1 + 1, id2, -1);
                ll cur = seg.qr(1, tt + 1).mi;
                if (cur >= 0) ans[idx++] = '1';
                else ans[idx++] = '0';
                seg.upd(id1 + 1, id2, 1);
            } else {
                seg.upd(id2 + 1, id1, 1);
                ll cur = seg.qr(1, tt + 1).mi;
                if (cur >= 0) ans[idx++] = '1';
                else ans[idx++] = '0';
                seg.upd(id2 + 1, id1, -1);
            }
        }
    }

    cout << ans << "\n";
}

int main() {
#ifdef LOCAL
    freopen("../in.txt", "r", stdin);
    freopen("../out.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> va[i];
        for (int i = 1; i <= m; i++) {
            int k;
            cin >> k;
            vb[i] = {};
            while (k--) {
                int b;
                cin >> b;
                vb[i].push_back(b);
            }
        }
        solve();
    }

    return 0;
}