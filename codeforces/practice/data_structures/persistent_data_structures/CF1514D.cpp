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
    int root[SZ];

    inline Seg() {
        init(1, SZ);
    }

    inline void init(int L, int R) {
        mem = 0, lb = L, rb = R;
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
            int cnt = tr[k].sum - tr[p].sum;
            if (cnt > lim) return cnt;
            return -1;
        }

        ll res = -1;
        ll lc = tr[ls(k)].sum - tr[ls(p)].sum;
        ll rc = tr[rs(k)].sum - tr[rs(p)].sum;
        if (lc > lim) res = max(res, query_lim(ls(k), ls(p), s, mid, lim));
        if (rc > lim) res = max(res, query_lim(rs(k), rs(p), mid + 1, e, lim));
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

const int N = 3e5 + 10;

int n, Q;
int a[N];

Seg<N> seg;

void solve() {
    seg.init(1, n);
    for (int i = 1; i <= n; i++) {
        seg.add(i, i - 1, a[i], 1);
    }

    while (Q--) {
        int L, R;
        cin >> L >> R;

        int lim = (R - L + 1 + 1) / 2;
        int cnt = seg.query_lim(L, R, lim);
        if (cnt == -1) {
            cout << 1 << "\n";
        } else {
            int cnt2 = R - L + 1 - cnt;
            cout << cnt - cnt2 << "\n";
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