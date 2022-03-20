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

    inline void push_up(Node &fa, Node &lc, Node &rc) {
        fa.sum = lc.sum + rc.sum;
        fa.mi = min(lc.mi, rc.mi);
    }

    inline void push_up(int k) {
        push_up(tr[k], tr[ls(k)], tr[rs(k)]);
    }

    inline void work(Node &t, ll sz, ll val) {
        t.sum = t.sum + sz * val;
        t.lz = t.lz + val;
        t.mi = t.mi + val;
    }

    inline void push_down(int k, int s, int e) {
        if (!ls(k)) ls(k) = new_node();
        if (!rs(k)) rs(k) = new_node();
        ll len = e - s + 1;
        ll lsz = len - len / 2, rsz = len / 2;
        if (tr[k].lz) {
            work(tr[ls(k)], lsz, tr[k].lz);
            work(tr[rs(k)], rsz, tr[k].lz);
            tr[k].lz = 0;
        }
    }

    inline void add(int &k, int s, int e, int L, int R, ll val) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            work(tr[k], e - s + 1, val);
            return;
        }

        push_down(k, s, e);
        if (L <= mid) add(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) add(rs(k), mid + 1, e, L, R, val);
        push_up(k);
    }

    inline void update(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = tr[k].mi = min(tr[k].mi, val);
            return;
        }

        push_down(k, s, e);
        if (id <= mid) update(ls(k), s, mid, id, val);
        if (id >= mid + 1) update(rs(k), mid + 1, e, id, val);
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

    inline Node query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k];

        push_down(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        Node res = {0};
        Node lc = query(ls(k), s, mid, L, R);
        Node rc = query(rs(k), mid + 1, e, L, R);
        push_up(res, lc, rc);
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

const int N = 1e5 + 10;

int n, m;
ll va[N];
vector<ll> vb[N];
Seg<2 * N> seg;

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
    for (int i = 1; i <= tt + 1; i++) seg.set(i, suf[i]);

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
                seg.add(id1 + 1, id2, -1);
                ll cur = seg.query(1, tt + 1).mi;
                if (cur >= 0) ans[idx++] = '1';
                else ans[idx++] = '0';
                seg.add(id1 + 1, id2, 1);
            } else {
                seg.add(id2 + 1, id1, 1);
                ll cur = seg.query(1, tt + 1).mi;
                if (cur >= 0) ans[idx++] = '1';
                else ans[idx++] = '0';
                seg.add(id2 + 1, id1, -1);
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