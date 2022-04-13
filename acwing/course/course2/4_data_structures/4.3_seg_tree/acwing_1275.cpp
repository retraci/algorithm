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

// region 区间最大值段树
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        ll sum, lz;
    };

    int lb, rb, rt, mem;
    Node tr[SZ * 4];

    inline Seg() {
        init(1, SZ);
    }

    inline void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        tr[0].lson = tr[0].rson = 0;
        tr[0].sum = tr[0].lz = 0;
    }

    inline void init(int L, int R, ll val) {
        init(L, R);
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++mem;
        tr[id].lson = tr[id].rson = 0;
        tr[id].sum = tr[id].lz = 0;
        return id;
    }

    inline void push_up(Node &fa, Node &lc, Node &rc) {
        fa.sum = max(lc.sum, rc.sum);
    }

    inline void push_up(int k) {
        push_up(tr[k], tr[ls(k)], tr[rs(k)]);
    }

    inline void work(Node &t, ll val) {
        t.sum = max(t.sum, val);
        t.lz = max(t.lz, val);
    }

    inline void push_down(int k, int s, int e) {
        if (!ls(k)) ls(k) = new_node();
        if (!rs(k)) rs(k) = new_node();
        if (tr[k].lz) {
            work(tr[ls(k)], tr[k].lz);
            work(tr[rs(k)], tr[k].lz);
            tr[k].lz = 0;
        }
    }

    inline void update(int &k, int s, int e, int L, int R, ll val) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            work(tr[k], val);
            return;
        }

        push_down(k, s, e);
        if (L <= mid) update(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) update(rs(k), mid + 1, e, L, R, val);
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

    inline void update(int L, int R, ll val) {
        if (R < L) return;
        update(rt, lb, rb, L, R, val);
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

const int N = 2e5 + 10;

int n, m;
Seg<N> seg;

void solve() {
    seg.init(1, n, 0);

    int pos = 0, lst = 0;
    while (n--) {
        string op;
        int x;
        cin >> op >> x;
        if (op == "A") {
            x = (1LL * x + lst) % m;
            seg.set(++pos, x);
        } else {
            lst = seg.query(pos - x + 1, pos).sum;
            cout << lst << "\n";
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
        cin >> n >> m;
        solve();
    }

    return 0;
}