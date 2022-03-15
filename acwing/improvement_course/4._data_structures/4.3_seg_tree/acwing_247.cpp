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

vector<double> lsh;

// region 扫描线线段树
template<int SZ>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (tr[x].lson)
#define rs(x) (tr[x].rson)

    struct Node {
        int lson, rson;
        ll sum;
        double v;
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

    inline void push_up(int k, int s, int e) {
        if (tr[k].sum) tr[k].v = lsh[e + 1] - lsh[s];
        else if (s != e) tr[k].v = tr[ls(k)].v + tr[rs(k)].v;
        else tr[k].v = 0;
    }

    inline void add(int &k, int s, int e, int L, int R, ll val) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            tr[k].sum = tr[k].sum + val;
            push_up(k, s, e);
            return;
        }

        if (L <= mid) add(ls(k), s, mid, L, R, val);
        if (R >= mid + 1) add(rs(k), mid + 1, e, L, R, val);
        push_up(k, s, e);
    }

    inline void set(int &k, int s, int e, int id, ll val) {
        if (!k) k = new_node();

        if (s == e) {
            tr[k].sum = val;
            push_up(k, s, e);
            return;
        }

        if (id <= mid) set(ls(k), s, mid, id, val);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, val);
        push_up(k, s, e);
    }

    inline double query(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return tr[k].v;

        if (R <= mid) return query(ls(k), s, mid, L, R);
        if (L >= mid + 1) return query(rs(k), mid + 1, e, L, R);
        return query(ls(k), s, mid, L, R) + query(rs(k), mid + 1, e, L, R);
    }

    inline void add(int L, int R, ll val) {
        if (R < L) return;
        add(rt, lb, rb, L, R, val);
    }

    inline void set(int id, ll val) {
        set(rt, lb, rb, id, val);
    }

    inline double query(int L, int R) {
        if (R < L) return 0;
        return query(rt, lb, rb, L, R);
    }
};
// endregion

typedef tuple<double, double, double, int> td3i;

const int N = 10010;

int n;
td3i a[N * 2];
int ti;

Seg<N * 2> seg;

void init() {
    lsh = {};
    for (int i = 1; i <= 2 * n; i++) {
        auto [_, y1, y2, __] = a[i];
        lsh.push_back(y1);
        lsh.push_back(y2);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
}

int get(double x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void solve() {
    init();

    int nl = lsh.size();
    seg.init(0, nl - 2, 0);

    sort(a + 1, a + 2 * n + 1, [](auto &a, auto &b) {
        return get<0>(a) < get<0>(b);
    });

    double ans = 0;
    for (int i = 1; i <= 2 * n; i++) {
        auto [x, y1, y2, k] = a[i];

        if (i - 1 >= 1) {
            auto [px, _, __, ___] = a[i - 1];
            ans += (x - px) * seg.tr[1].v;
        }

        int L = get(y1), R = get(y2) - 1;
        seg.add(L, R, k);
    }

    cout << "Test case #" << ++ti << "\n";
    cout << fixed << setprecision(2);
    cout << "Total explored area: " << ans << "\n";
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
//    cin >> T;
    while (cin >> n, n) {
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            a[++cnt] = {x1, y1, y2, 1};
            a[++cnt] = {x2, y1, y2, -1};
        }
        solve();
    }

    return 0;
}