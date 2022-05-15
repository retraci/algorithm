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
#include <functional>

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

    Fhq() : plus(Info::plus) {
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

int n, m;
Fhq<Info, Tag, N> fhq;

void solve() {
    int cur = 0, cnt = 0;
    while (n--) {
        string op;
        int x;
        cin >> op >> x;

        if (op == "I") {
            if (x >= m) fhq.ins({x - cur, 1});
        }
        if (op == "A") cur += x;
        if (op == "S") {
            cur -= x;
            cnt += fhq.del_left(m - cur - 1);
        }
        if (op == "F") {
            auto t = fhq.kth(fhq.size() - x + 1);
            if (t.sz == 0) cout << -1 << "\n";
            else  cout << t.val + cur << "\n";
        }
    }

    cout << cnt << "\n";
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
        solve();
    }

    return 0;
}