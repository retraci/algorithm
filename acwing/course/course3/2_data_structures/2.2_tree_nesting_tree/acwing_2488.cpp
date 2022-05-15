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
#include <cmath>
#include <random>

void debug() {
    std::cout << "\n";
}

template<class T, class... OtherArgs>
void debug(T &&var, OtherArgs &&... args) {
    std::cout << std::forward<T>(var) << " ";
    debug(std::forward<OtherArgs>(args)...);
}

using namespace std;

#define fi first
#define se second
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using pii = pair<int, int>;

// region 线段树 套 x
template<class OInfo, class Info, class Tag, int SZ>
struct OSeg {
#define mid (s + e >> 1)
#define ls(x) (oinfo[x].lson)
#define rs(x) (oinfo[x].rson)

    int lb, rb, rt, mem;
    OInfo oinfo[SZ * 4];

    OSeg() {}

    void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        oinfo[0] = OInfo();
    }

    int new_node() {
        int id = ++mem;
        oinfo[id] = OInfo();
        return id;
    }

    void upd(int id, int pv, int nv) {
        upd(rt, lb, rb, id, pv, nv);
    }

    void upd(int &k, int s, int e, int id, int pv, int nv) {
        if (!k) k = new_node();

        oinfo[k].apply(pv, nv);
        if (s == e) return;

        if (id <= mid) upd(ls(k), s, mid, id, pv, nv);
        if (id >= mid + 1) upd(rs(k), mid + 1, e, id, pv, nv);
    }

    void build(int L, int R, int a[]) {
        build(rt, L, R, a);
    }

    void build(int &k, int s, int e, int a[]) {
        if (!k) k = new_node();

        oinfo[k].init(s, e, a);
        if (s == e) return;
        build(ls(k), s, mid, a), build(rs(k), mid + 1, e, a);
    }

    int get_rk(int L, int R, int x) {
        return get_rk(rt, lb, rb, L, R, x) + 1;
    }

    int get_rk(int k, int s, int e, int L, int R, int x) {
        if (L <= s && e <= R) return oinfo[k].get_rk(x);

        if (R <= mid) return get_rk(ls(k), s, mid, L, R, x);
        if (L >= mid + 1) return get_rk(rs(k), mid + 1, e, L, R, x);
        return get_rk(ls(k), s, mid, L, R, x) + get_rk(rs(k), mid + 1, e, L, R, x);
    }

    int get_kth(int L, int R, int x) {
        int left = 0, right = 1e8;
        while (left < right) {
            int md = left + right + 1 >> 1;
            int t = get_rk(L, R, md);
            if (t <= x) left = md;
            else right = md - 1;
        }
    }

    int get_pre(int L, int R, int x) {
        return get_pre(rt, lb, rb, L, R, x);
    }

    int get_pre(int k, int s, int e, int L, int R, int x) {
        if (L <= s && e <= R) return oinfo[k].get_pre(x);

        if (R <= mid) return get_pre(ls(k), s, mid, L, R, x);
        if (L >= mid + 1) return get_pre(rs(k), mid + 1, e, L, R, x);
        return max(get_pre(ls(k), s, mid, L, R, x), get_pre(rs(k), mid + 1, e, L, R, x));
    }

    int get_nxt(int L, int R, int x) {
        return get_nxt(rt, lb, rb, L, R, x);
    }

    int get_nxt(int k, int s, int e, int L, int R, int x) {
        if (L <= s && e <= R) return oinfo[k].get_nxt(x);

        if (R <= mid) return get_nxt(ls(k), s, mid, L, R, x);
        if (L >= mid + 1) return get_nxt(rs(k), mid + 1, e, L, R, x);
        return min(get_nxt(ls(k), s, mid, L, R, x), get_nxt(rs(k), mid + 1, e, L, R, x));
    }
};
// endregion

// region x 套 set
struct Tag {
    int pv, nv;

    Tag(int pv = -1, int nv = -1) : pv(pv), nv(nv) {}
};

using Info = int;

struct OInfo {
    int lson, rson;
    multiset<int> st;

    OInfo() : lson(0), rson(0) {}

    void init(int s, int e, int a[]) {
        for (int i = s; i <= e; i++) st.insert(a[i]);
        st.insert(-1e9), st.insert(1e9);
    }

    void apply(int pv, int nv) {
        st.erase(st.find(pv));
        st.insert(nv);
    }

    int get_pre(int x) {
        auto it = st.lower_bound(x);
        it = prev(it);
        return *it;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 5e4 + 10;

int n, m;
int a[N];
OSeg<OInfo, Info, Tag, N> seg;

void solve() {
    seg.init(1, n);
    seg.build(1, n, a);

    while (m--) {
        int op;
        cin >> op;

        if (op == 1) {
            int p, x;
            cin >> p >> x;

            seg.upd(p, a[p], x);
            a[p] = x;
        }
        if (op == 2) {
            int L, R, x;
            cin >> L >> R >> x;

            cout << seg.get_pre(L, R, x) << "\n";
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
    int _ = 1;
//    cin >> _;
    while (_--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}