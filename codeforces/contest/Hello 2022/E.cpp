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
namespace hash_func {
    template<typename TT>
    struct tuple_hash {
        size_t operator()(TT const &tt) const {
            return std::hash<TT>()(tt);
        }
    };

    template<class T>
    inline void hash_combine(std::size_t &seed, T const &v) {
        seed ^= hash_func::tuple_hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
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
}
// endregion
// region grid_delta
namespace grid_delta {
    // 上, 右, 下, 左  |  左上, 右上, 左下, 右下
    const int dx[9] = {-1, 0, 1, 0, -1, -1, 1, 1, 0};
    const int dy[9] = {0, 1, 0, -1, -1, 1, -1, 1, 0};
}
// endregion
// region general
#define ll long long
#define fi first
#define se second

typedef std::pair<int, int> pii;
typedef std::pair<ll, ll> pll;
typedef std::tuple<int, int, int> ti3;
typedef std::tuple<ll, ll, ll> tl3;
typedef std::tuple<int, int, int, int> ti4;
typedef std::tuple<ll, ll, ll, ll> tl4;
// endregion
// region 区间最小值线段树
namespace seg {
#define mid (left + right >> 1)
#define lson (node << 1)
#define rson ((node << 1) + 1)

    const int SZ = 2e5;

    struct Node {
        int left, right;
        ll sum, lz, mi;
    };

    Node tree[SZ * 4];
    std::vector<ll> lsh;

    inline int get_id(ll x) {
        return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
    }

    inline void push_up(int node) {
        tree[node].sum = tree[lson].sum + tree[rson].sum;
        tree[node].mi = std::min(tree[lson].mi, tree[rson].mi);
    }

    inline void push_down(int node) {
        ll lsz = tree[lson].right - tree[lson].left + 1;
        ll rsz = tree[rson].right - tree[rson].left + 1;
        if (tree[node].lz) {
            tree[lson].sum = tree[lson].sum + lsz * tree[node].lz;
            tree[rson].sum = tree[rson].sum + rsz * tree[node].lz;
            tree[lson].lz = tree[lson].lz + tree[node].lz;
            tree[rson].lz = tree[rson].lz + tree[node].lz;
            tree[node].lz = 0;
        }
    }

    void build(int node, int left, int right) {
        tree[node].left = left, tree[node].right = right;
        tree[node].sum = tree[node].mi = tree[node].lz = 0;

        if (left == right) return;
        build(lson, left, mid);
        build(rson, mid + 1, right);
    }

    void update(int node, int L, int R, ll val) {
        int left = tree[node].left, right = tree[node].right;

        if (right < L || left > R) return;
        if (L <= left && right <= R) {
            tree[node].sum = tree[node].sum + (R - L + 1) * val;
            tree[node].lz = tree[node].lz + val;
            tree[node].mi = tree[node].mi + val;
            return;
        }

        push_down(node);
        update(lson, L, R, val);
        update(rson, L, R, val);
        push_up(node);
    }

    ll query(int node, int L, int R) {
        int left = tree[node].left, right = tree[node].right;

        if (right < L || left > R) return 1e18;
        if (L <= left && right <= R) return tree[node].mi;

        push_down(node);
        return std::min(query(lson, L, R), query(rson, L, R));
    }
}
// endregion

using namespace std;
using namespace grid_delta;
using namespace seg;

const int N = 1e5 + 10;

int n, m;
ll va[N];
vector<ll> vb[N];

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

    build(1, 1, tt + 1);
    for (int i = 1; i <= tt; i++) update(1, i, i, suf[i]);

    string ans(K, '0');
    int idx = 0;
    for (int i = 1; i <= m; i++) {
        for (int x : vb[i]) {
            ll sz = vb[i].size() - 1;
            ll s = (vc[i] + vb[i].size() - 1) / vb[i].size();
            ll ns = ((vc[i] - x + sz - 1) / sz);
            ll id1 = lower_bound(vd + 1, vd + 1 + tt, (pll) {s, 1}) - vd;
            ll id2 = lower_bound(vd + 1, vd + 1 + tt, (pll) {ns, 1}) - vd;

            if (id1 < id2) {
                update(1, id1 + 1, id2, -1);
                ll cur = query(1, 1, tt + 1);
                if (cur >= 0) ans[idx++] = '1';
                else ans[idx++] = '0';
                update(1, id1 + 1, id2, 1);
            } else {
                update(1, id2 + 1, id1, 1);
                ll cur = query(1, 1, tt + 1);
                if (cur >= 0) ans[idx++] = '1';
                else ans[idx++] = '0';
                update(1, id2 + 1, id1, -1);
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

    auto prework = [&]() -> void {
    };
    prework();

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