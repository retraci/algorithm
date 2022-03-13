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

// region 动态开点普通线段树
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

    inline void init(int L = 1, int R = SZ, int val = 0) {
        lb = L, rb = R;
        for (int i = L; i <= R; i++) set(i, val);
    }

    inline int new_node() {
        int id = ++nw;
        return id;
    }

    inline void push_up(int k) {
        tr[k].sum = tr[ls(k)].sum + tr[rs(k)].sum;
    }

    inline void push_down(int k, int s, int e) {
        if (!ls(k)) ls(k) = new_node();
        if (!rs(k)) rs(k) = new_node();
        ll len = e - s + 1;
        ll lsz = len - len / 2, rsz = len / 2;
        if (tr[k].lz) {
            tr[ls(k)].sum = tr[ls(k)].sum + lsz * tr[k].lz;
            tr[rs(k)].sum = tr[rs(k)].sum + rsz * tr[k].lz;
            tr[ls(k)].lz = tr[ls(k)].lz + tr[k].lz;
            tr[rs(k)].lz = tr[rs(k)].lz + tr[k].lz;
            tr[k].lz = 0;
        }
    }

    inline void update(int &k, int s, int e, int L, int R, ll val) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            tr[k].sum = tr[k].sum + (e - s + 1) * val;
            tr[k].lz = tr[k].lz + val;
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
        return query(ls(k), s, mid, L, R) + query(rs(k), mid + 1, e, L, R);
    }

    inline ll query_k(int k, int s, int e, int x) {
        if (s == e) return s;

        if (x <= tr[ls(k)].sum) return query_k(ls(k), s, mid, x);
        else return query_k(rs(k), mid + 1, e, x - tr[ls(k)].sum);
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

    inline ll query_k(int x) {
        return query_k(rt, lb, rb, x);
    }
};
// endregion

const int N = 1e5 + 10;

int n, m;
int a[N];
ti3 b[N];

vector<int> lsh;
Seg<N * 2> seg;

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void solve() {
    lsh.clear();
    for (int i = 1; i <= n; i++) lsh.push_back(a[i]);
    for (int i = 1; i <= m; i++) {
        auto [L, R, h] = b[i];
        lsh.push_back(h);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());

    seg.init(1, lsh.size());
    vector<int> qs[n + 1];
    unordered_map<int, int> ask[n + 1];
    for (int i = 1; i <= m; i++) {
        auto [L, R, h] = b[i];
        h = get(h) + 1;

        qs[L - 1].push_back(h);
        qs[R].push_back(h);
    }

    for (int i = 1; i <= n; i++) {
        int x = get(a[i]) + 1;
        seg.update(x, x, 1);

        for (int h : qs[i]) {
            ask[i][h] = seg.query(1, h);
        }
    }

    for (int i = 1; i <= m; i++) {
        auto [L, R, h] = b[i];
        h = get(h) + 1;

        cout << ask[R][h] - ask[L - 1][h] << " ";
    }
    cout << "\n";
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
        for (int i = 1; i <= m; i++) {
            int L, R, h;
            cin >> L >> R >> h;
            b[i] = {L, R, h};
        }

        solve();
    }

    return 0;
}