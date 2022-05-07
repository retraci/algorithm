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
std::mt19937 rnd = std::mt19937(233);
template<class Info, class Tag, int SZ,
        class Plus = std::plus<Info>>
struct Fhq {
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)
    const Plus plus;
    int rt, mem;
    Info info[SZ + 10];

    Fhq() : plus(Plus()) {
        init();
    }

    void init() {
        rt = 0, mem = 0;
        info[0] = Info();
    }

    int new_node() {
        int id = ++mem;
        info[id] = Info();
        return id;
    }

    void pull(int k) {
        info[k].set(plus(info[ls(k)], info[rs(k)]));
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

    void ins(int val) {
        int x, y;
        split(rt, val, x, y);
        int t = new_node();
        info[t] = Info(val, rnd(), 1);
        rt = merge(merge(x, t), y);
    }

    void del(int val) {
        int x, y, z;
        split(rt, val, x, z);
        split(x, val - 1, x, y);
        y = merge(ls(y), rs(y));
        rt = merge(merge(x, y), z);
    }

    int kth(int rk) {
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

        return info[k].val;
    }

    int get_rk(int val) {
        int x, y;
        split(rt, val - 1, x, y);
        int res = info[x].sz + 1;

        rt = merge(x, y);
        return res;
    }

    int get_pre(int val) {
        int x, y;
        split(rt, val - 1, x, y);
        int k = x;
        while (rs(k)) k = rs(k);
        int res = info[k].val;

        rt = merge(x, y);
        return res;
    }

    int get_nxt(int val) {
        int x, y;
        split(rt, val, x, y);
        int k = y;
        while (ls(k)) k = ls(k);
        int res = info[k].val;

        rt = merge(x, y);
        return res;
    }
};
// endregion

// region 普通平衡树(fhq)
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

    Info(int val = 0, int key = 0, int sz = 0) : lson(0), rson(0), val(val), key(key), sz(sz) {}

    void apply(const Tag &a) {
        if (!a.check()) return;
        swap(lson, rson);
    }

    friend Info operator+(const Info &a, const Info &b) {
        return {0, 0, a.sz + b.sz + 1};
    }

    void set(const Info &a) {
        sz = a.sz;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 100010;

int n;
pii a[N];
Fhq<Info, Tag, N> fhq;

void solve() {
    fhq.init();
    for (int i = 1; i <= n; i++) {
        auto [op, x] = a[i];

        if (op == 1) fhq.ins(x);
        if (op == 2) fhq.del(x);
        if (op == 3) cout << fhq.get_rk(x) << "\n";
        if (op == 4) cout << fhq.kth(x) << "\n";
        if (op == 5) cout << fhq.get_pre(x) << "\n";
        if (op == 6) cout << fhq.get_nxt(x) << "\n";
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i].fi >> a[i].se;
        solve();
    }

    return 0;
}