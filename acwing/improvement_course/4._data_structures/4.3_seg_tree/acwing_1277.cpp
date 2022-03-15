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

// region 普通线段树
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        ll sum, ad_lz, mu_lz;
    };

    int MOD;

    int lb, rb, rt;
    Node tr[SZ * 4];
    int nw;

    inline Seg() {
        init(1, SZ, 0);
    }

    inline void init(int L, int R, int _MOD) {
        nw = 0, lb = L, rb = R, MOD = _MOD;
    }

    inline void init(int L, int R, ll val) {
        nw = 0, lb = L, rb = R;
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++nw;
        tr[id].lson = tr[id].rson = 0;
        tr[id].sum = tr[id].ad_lz = 0;
        tr[id].mu_lz = 1;
        return id;
    }

    inline void work(Node &t, ll sz, ll ad, ll mu) {
        t.sum = (t.sum * mu % MOD + ad * sz % MOD) % MOD;
        t.ad_lz = (t.ad_lz * mu % MOD + ad) % MOD;
        t.mu_lz = t.mu_lz * mu % MOD;
    }

    inline void push_up(int k) {
        tr[k].sum = (tr[ls(k)].sum + tr[rs(k)].sum) % MOD;
    }

    inline void push_down(int k, int s, int e) {
        if (!ls(k)) ls(k) = new_node();
        if (!rs(k)) rs(k) = new_node();
        ll len = e - s + 1;
        ll lsz = len - len / 2, rsz = len / 2;
        if (tr[k].ad_lz != 0 || tr[k].mu_lz != 1) {
            work(tr[ls(k)], lsz, tr[k].ad_lz, tr[k].mu_lz);
            work(tr[rs(k)], rsz, tr[k].ad_lz, tr[k].mu_lz);
            tr[k].ad_lz = 0, tr[k].mu_lz = 1;
        }
    }

    inline void update(int &k, int s, int e, int L, int R, ll ad, ll mu) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            work(tr[k], e - s + 1, ad, mu);
            return;
        }

        push_down(k, s, e);
        if (L <= mid) update(ls(k), s, mid, L, R, ad, mu);
        if (R >= mid + 1) update(rs(k), mid + 1, e, L, R, ad, mu);
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
        return (query(ls(k), s, mid, L, R) + query(rs(k), mid + 1, e, L, R)) % MOD;
    }

    inline void update(int L, int R, ll ad, ll mu) {
        if (R < L) return;
        update(rt, lb, rb, L, R, ad, mu);
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

const int N = 1e5 + 10;

int n, Q, P;
int a[N];

Seg<N> seg;

void solve() {
    seg.init(1, n, P);
    for (int i = 1; i <= n; i++) seg.set(i, a[i]);

    cin >> Q;
    while (Q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int L, R, x;
            cin >> L >> R >> x;

            seg.update(L, R, 0, x);
        } else if (op == 2) {
            int L, R, x;
            cin >> L >> R >> x;

            seg.update(L, R, x, 1);
        } else {
            int L, R;
            cin >> L >> R;

            cout << seg.query(L, R) << "\n";
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
        cin >> n >> P;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}