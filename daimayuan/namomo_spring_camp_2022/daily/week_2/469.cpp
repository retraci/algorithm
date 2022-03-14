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

// region 动态开点区间最小值段树
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        ll sum, lz;
    };

    int lb, rb, rt;
    Node tr[SZ * 4];
    int nw;

    inline Seg() {
        lb = 1, rb = SZ;
    }

    inline void init(int L = 1, int R = SZ, ll val = 1e18) {
        lb = L, rb = R;
        for (int i = 1; i < SZ * 4; i++) tr[i].sum = tr[i].lz = 1e18;
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++nw;
        return id;
    }

    inline void push_up(int k) {
        tr[k].sum = min(tr[ls(k)].sum, tr[rs(k)].sum);
    }

    inline void push_down(int k, int s, int e) {
        if (!ls(k)) ls(k) = new_node();
        if (!rs(k)) rs(k) = new_node();
        if (tr[k].lz) {
            tr[ls(k)].sum = min(tr[ls(k)].sum, tr[k].lz);
            tr[rs(k)].sum = min(tr[rs(k)].sum, tr[k].lz);
            tr[ls(k)].lz = min(tr[ls(k)].lz, tr[k].lz);
            tr[rs(k)].lz = min(tr[rs(k)].lz, tr[k].lz);
            tr[k].lz = 1e18;
        }
    }

    inline void update(int &k, int s, int e, int L, int R, ll val) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            tr[k].sum = min(tr[k].sum, val);
            tr[k].lz = min(tr[k].lz, val);
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

    inline ll query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k].sum;

        push_down(k, s, e);
        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        return min(query(ls(k), s, mid, L, R), query(rs(k), mid + 1, e, L, R));
    }

    inline void update(int L, int R, ll val) {
        if (R < L) return;
        update(rt, lb, rb, L, R, val);
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

const int N = 5e5 + 10;

int n, Q;
int a[N];
ti3 qs[N];
int ans[N];

Seg<N> seg;

void solve() {
    sort(qs + 1, qs + Q + 1, [](auto &a, auto &b) {
        return get<1>(a) < get<1>(b);
    });

    seg.init(1, n, 1e9);
    int pos = 1;
    unordered_map<int, int> lst;
    for (int i = 1; i <= Q; i++) {
        auto [L, R, id] = qs[i];
        while (pos <= R) {
            int x = a[pos];
            if (lst.count(x)) seg.update(1, lst[x], pos - lst[x]);
            lst[x] = pos++;
        }

        int ret = seg.query(L, R);
        ans[id] = ret == 1e9 ? -1 : ret;
    }

    for (int i = 1; i <= Q; i++) cout << ans[i] << "\n";
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
        for (int i = 1; i <= Q; i++) {
            int L, R;
            cin >> L >> R;
            qs[i] = {L, R, i};
        }

        solve();
    }

    return 0;
}