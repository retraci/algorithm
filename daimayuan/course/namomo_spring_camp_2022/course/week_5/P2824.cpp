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
        int sum, lz;
    };

    int lb, rb, rt, mem;
    Node tr[SZ * 4];

    inline Seg() {
        init(1, SZ);
    }

    inline void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        tr[0].lson = tr[0].rson = 0;
        tr[0].sum = 0;
        tr[0].lz = -1;
    }

    inline void init(int L, int R, int val) {
        init(L, R);
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        tr[id].sum = 0;
        tr[id].lz = -1;
        return id;
    }

    inline void push_up(Node &fa, Node &lc, Node &rc) {
        fa.sum = lc.sum + rc.sum;
    }

    inline void push_up(int k) {
        push_up(tr[k], tr[ls(k)], tr[rs(k)]);
    }

    inline void work(Node &t, int sz, int val) {
        t.sum = val * sz;
        t.lz = val;
    }

    inline void push_down(int k, int s, int e) {
        int len = e - s + 1;
        int lsz = len - len / 2, rsz = len / 2;
        if (~tr[k].lz) {
            if (!ls(k)) ls(k) = new_node();
            if (!rs(k)) rs(k) = new_node();
            work(tr[ls(k)], lsz, tr[k].lz);
            work(tr[rs(k)], rsz, tr[k].lz);
            tr[k].lz = -1;
        }
    }

    inline void add(int &k, int s, int e, int L, int R, int val) {
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

    inline void set(int &k, int s, int e, int id, int val) {
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

    inline void add(int L, int R, int val) {
        if (R < L) return;
        add(rt, lb, rb, L, R, val);
    }

    inline void set(int id, int val) {
        set(rt, lb, rb, id, val);
    }

    inline Node query(int L, int R) {
        if (R < L) return {0};
        return query(rt, lb, rb, L, R);
    }
};
// endregion

const int N = 1e5 + 10;

int n, m, q;
int a[N];
ti3 b[N];

Seg<N> seg;

bool check(int md) {
    for (int i = 1; i <= n; i++) seg.set(i, a[i] >= md);

    for (int i = 1; i <= m; i++) {
        auto [op, L, R] = b[i];

        auto t = seg.query(L, R);
        int c1 = t.sum, c0 = R - L + 1 - c1;
        if (op) {
            seg.add(L, L + c1 - 1, 1), seg.add(L + c1, R, 0);
        } else {
            seg.add(L, L + c0 - 1, 0), seg.add(L + c0, R, 1);
        }
    }

    return seg.query(q, q).sum;
}

void solve() {
    seg.init(1, n);
    int left = 1, right = n;
    while (left < right) {
        int md = left + right + 1 >> 1;
        if (check(md)) left = md;
        else right = md - 1;
    }

    cout << left << "\n";
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
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= m; i++) {
            int op, L, R;
            cin >> op >> L >> R;
            b[i] = {op, L, R};
        }
        cin >> q;
        solve();
    }

    return 0;
}