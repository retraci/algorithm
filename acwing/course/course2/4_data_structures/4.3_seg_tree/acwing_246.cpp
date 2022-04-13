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

// region 区间修改, 维护最大值线段树
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        ll sum, v;
    };

    int lb, rb, rt;
    Node tr[SZ * 4];
    int nw;

    inline Seg() {
        init(1, SZ);
    }

    inline void init(int L, int R) {
        nw = 0, lb = L, rb = R;
    }

    inline void init(int L, int R, ll val) {
        nw = 0, lb = L, rb = R;
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++nw;
        tr[id].lson = tr[id].rson = 0;
        tr[id].sum = tr[id].v = 0;
        return id;
    }

    inline void push_up(Node &fa, Node &ls, Node &rs) {
        fa.sum = ls.sum + rs.sum;
        fa.v = __gcd(ls.v, rs.v);
    }

    inline void push_up(int k) {
        push_up(tr[k], tr[ls(k)], tr[rs(k)]);
    }

    inline void add(int &k, int s, int e, int L, int R, ll val) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            tr[k].sum = tr[k].sum + (e - s + 1) * val;
            tr[k].v = tr[k].sum;
            return;
        }

        if (L <= mid) add(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) add(rs(k), mid + 1, e, L, R, val);
        push_up(k);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = tr[k].v = val;
            return;
        }

        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        push_up(k);
    }

    inline Node query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k];

        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);

        Node ls = query(ls(k), s, mid, L, R);
        Node rs = query(rs(k), mid + 1, e, L, R);
        Node res;
        push_up(res, ls, rs);
        return res;
    }

    inline void add(int L, int R, ll val) {
        if (R < L) return;
        add(rt, lb, rb, L, R, val);
    }

    inline void set(int id, ll val) {
        set(rt, lb, rb, id, val);
    }

    inline Node query(int L, int R) {
        if (R < L) return {};
        return query(rt, lb, rb, L, R);
    }
};
// endregion

const int N = 500010;

int n, Q;
ll a[N];

Seg<N> seg;

void solve() {
    seg.init(1, n + 1);
    for (int i = 1; i <= n; i++) seg.set(i, a[i] - a[i - 1]);

    while (Q--) {
        string op;
        cin >> op;
        if (op == "Q") {
            int L, R;
            cin >> L >> R;

            ll al = seg.query(1, L).sum;
            cout << abs(__gcd(al, seg.query(L + 1, R).v)) << "\n";
        } else {
            ll L, R, x;
            cin >> L >> R >> x;

            seg.add(L, L, x);
            seg.add(R + 1, R + 1, -x);
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