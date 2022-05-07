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

// region 普通平衡树(fhq)
mt19937 rnd(random_device{}());
template<class Info, class Tag, int SZ>
struct Fhq {
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)

    Info (*plus)(const Info &p, const Info &a, const Info &b);
    int rt, mem;
    Info info[SZ + 10];

    Fhq() : plus(Info::plus) {}

    void init() {
        rt = 0, mem = 0;
        info[0] = Info();
    }

    int new_node() {
        int id = ++mem;
        info[id] = Info();
        return id;
    }

    int size() {
        return info[rt].sz;
    }

    void pull(int k) {
        info[k].set(plus(info[k], info[ls(k)], info[rs(k)]));
    }

    void split(int k, int val, int &x, int &y) {
        if (!k) {
            x = y = 0;
            return;
        }

        if (info[k].val <= val) {
            x = k;
            split(rs(k), val, rs(k), y);
        } else {
            y = k;
            split(ls(k), val, x, ls(k));
        }
        pull(k);
    }

    int merge(int x, int y) {
        if (!x || !y) return x | y;

        if (info[x].key > info[y].key) {
            rs(x) = merge(rs(x), y);
            pull(x);
            return x;
        } else {
            ls(y) = merge(x, ls(y));
            pull(y);
            return y;
        }
    }

    int build(int L, int R, Info a[]) {
        if (L > R) return 0;
        if (L == R) {
            int t = new_node();
            info[t] = a[L];
            info[t].init();
            return t;
        }

        int mid = L + R >> 1, k = new_node();
        info[k] = a[mid];
        info[k].init();
        ls(k) = build(L, mid - 1, a);
        rs(k) = build(mid + 1, R, a);
        pull(k);
        return k;
    }

    void insarr(int p, int len, Info a[]) {
        int x, y;
        split(rt, p, x, y);

        int nt = build(1, len, a);
        rt = merge(merge(x, nt), y);
    }

    void ins(const Info &v) {
        int x, y;
        split(rt, v.val, x, y);

        int t = new_node();
        info[t] = v;
        info[t].init();
        rt = merge(merge(x, t), y);
    }

    void del(int val) {
        int x, y, z;
        split(rt, val - 1, x, y);
        split(y, val, y, z);

        y = merge(ls(y), rs(y));
        rt = merge(merge(x, y), z);
    }

    int del_left(int val) {
        int x, y;
        split(rt, val, x, y);

        rt = y;
        return info[x].sz;
    }

    int del_right(int val) {
        int x, y;
        split(rt, val - 1, x, y);

        rt = x;
        return info[y].sz;
    }

    Info kth(int rk) {
        if (rk < 1 || rk > size()) return Info();

        int k = rt;
        while (k) {
            if (info[ls(k)].sz + 1 == rk) break;

            if (info[ls(k)].sz >= rk) {
                k = ls(k);
            } else {
                rk -= info[ls(k)].sz + 1;
                k = rs(k);
            }
        }

        return info[k];
    }

    int get_rk(int val) {
        int x, y;
        split(rt, val - 1, x, y);

        int res = info[x].sz + 1;

        rt = merge(x, y);
        return res;
    }

    Info get_pre(int val) {
        int x, y;
        split(rt, val - 1, x, y);

        int k = x;
        while (rs(k)) k = rs(k);
        Info res = info[k];

        rt = merge(x, y);
        return res;
    }

    Info get_nxt(int val) {
        int x, y;
        split(rt, val, x, y);

        int k = y;
        while (ls(k)) k = ls(k);
        Info res = info[k];

        rt = merge(x, y);
        return res;
    }
};
// endregion

// region 文艺平衡树(fhq)
struct Tag {
    int x;

    Tag(int x = 0) : x(x) {}

    bool check() const {
        return x != 0;
    }

    void apply(const Tag &a) {
        if (!a.check()) return;
        x ^= a.x;
    }
};

struct Info {
    int lson, rson, key, val;
    int sz;

    Info(int val = 0, int sz = 0) : lson(0), rson(0), val(val), sz(sz) {}

    void init() {
        key = rnd();
    }

    void apply(const Tag &a) {
        if (!a.check()) return;
        swap(lson, rson);
    }

    static Info plus(const Info &p, const Info &a, const Info &b) {
        return {0, a.sz + b.sz + 1};
    }

    void set(const Info &a) {
        sz = a.sz;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;
const int M = 1e6 + 10;

int n, m;
int a[N];
Info buf[N];
pii qs[M];
Fhq<Info, Tag, N + M> fhq;

void solve() {
    fhq.init();
    for (int i = 1; i <= n; i++) buf[i] = {a[i], 1};
    sort(buf + 1, buf + n + 1, [](auto &a, auto &b) {
        return a.val < b.val;
    });
    fhq.insarr(0, n, buf);

    int ans = 0, lst = 0;
    for (int i = 1; i <= m; i++) {
        auto [op, x] = qs[i];
        x ^= lst;

        int t = 0;
        if (op == 1) fhq.ins({x, 1});
        if (op == 2) fhq.del(x);
        if (op == 3) t = fhq.get_rk(x), lst = t, ans ^= t;
        if (op == 4) t = fhq.kth(x).val, lst = t, ans ^= t;
        if (op == 5) t = fhq.get_pre(x).val, lst = t, ans ^= t;
        if (op == 6) t = fhq.get_nxt(x).val, lst = t, ans ^= t;
    }
    cout << ans << "\n";
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
        for (int i = 1; i <= m; i++) cin >> qs[i].fi >> qs[i].se;
        solve();
    }

    return 0;
}