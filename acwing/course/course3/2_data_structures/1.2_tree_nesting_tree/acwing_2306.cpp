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

// region 区修线段树
template<class Info, class Tag, int SZ,
        class Plus = std::plus<Info>>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)

    const Plus plus;
    int lb, rb, root[SZ + 10], cnt, mem;
    Info info[SZ * 4];
    Tag tag[SZ * 4];

    Seg() : plus(Plus()) {}

    void init(int L, int R) {
        cnt = 0, mem = 0, lb = L, rb = R;
    }

    int new_tree() {
        int tid = ++cnt;
        root[tid] = 0;
        return tid;
    }

    int new_node() {
        int id = ++mem;
        info[id] = Info();
        tag[id] = Tag();
        return id;
    }

    void pull(int k) {
        info[k].set(plus(info[ls(k)], info[rs(k)]));
    }

    void apply(int k, int s, int e, const Tag &v) {
        info[k].apply(s, e, v);
        tag[k].apply(s, e, v);
    }

    void push(int k, int s, int e) {
        if (tag[k].check()) {
            if (!ls(k)) ls(k) = new_node();
            if (!rs(k)) rs(k) = new_node();
            apply(ls(k), s, mid, tag[k]);
            apply(rs(k), mid + 1, e, tag[k]);
            tag[k] = Tag();
        }
    }

    void upd(int &k, int s, int e, int L, int R, const Tag &v) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            apply(k, s, e, v);
            return;
        }

        push(k, s, e);
        if (L <= mid) upd(ls(k), s, mid, L, R, v);
        if (R >= mid + 1) upd(rs(k), mid + 1, e, L, R, v);
        pull(k);
    }

    void set(int &k, int s, int e, int id, const Info &v) {
        if (!k) k = new_node();

        if (s == e) {
            info[k].set(v);
            return;
        }

        push(k, s, e);
        if (id <= mid) set(ls(k), s, mid, id, v);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, v);
        pull(k);
    }

    Info qr(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return info[k];

        push(k, s, e);
        if (R <= mid) return qr(ls(k), s, mid, L, R);
        if (L >= mid + 1) return qr(rs(k), mid + 1, e, L, R);
        return plus(qr(ls(k), s, mid, L, R), qr(rs(k), mid + 1, e, L, R));
    }

    int kth(int k, int s, int e, ll x) {
        if (s == e) return x <= info[k].sum ? s : rb + 1;

        push(k, s, e);
        if (x <= info[ls(k)].sum) return kth(ls(k), s, mid, x);
        else return kth(rs(k), mid + 1, e, x - info[ls(k)].sum);
    }

    void upd(int tid, int L, int R, const Tag &v) {
        if (R < L) return;
        int &rt = root[tid];
        upd(rt, lb, rb, L, R, v);
    }

    void set(int tid, int id, const Info &v) {
        int &rt = root[tid];
        set(rt, lb, rb, id, v);
    }

    Info qr(int tid, int L, int R) {
        if (R < L) return Info();
        int rt = root[tid];
        return qr(rt, lb, rb, L, R);
    }

    int kth(int tid, ll x) {
        int rt = root[tid];
        return kth(rt, lb, rb, x);
    }
};
// endregion

// region 区间求和
struct Tag {
    ll x;

    Tag(ll x = 0) : x(x) {}

    bool check() const {
        return x != 0;
    }

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        x += a.x;
    }
};

struct Info {
    int lson, rson;
    ll sum;

    Info(ll sum = 0) : lson(0), rson(0), sum(sum) {}

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        sum += (e - s + 1) * a.x;
    }

    friend Info operator+(const Info &a, const Info &b) {
        return a.sum + b.sum;
    }

    void set(const Info &a) {
        sum = a.sum;
    }
};
// endregion

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

    void upd(int id, int L, int R) {
        upd(rt, lb, rb, id, L, R);
    }

    void upd(int &k, int s, int e, int id, int L, int R) {
        if (!k) k = new_node();

        oinfo[k].apply(L, R);
        if (s == e) return;

        if (id <= mid) upd(ls(k), s, mid, id, L, R);
        if (id >= mid + 1) upd(rs(k), mid + 1, e, id, L, R);
    }

    int kth(int L, int R, int x) {
        return kth(rt, lb, rb, L, R, x);
    }

    int kth(int k, int s, int e, int L, int R, int x) {
        if (s == e) return s;

        ll t = oinfo[rs(k)].get(L, R);
        if (x <= t) return kth(rs(k), mid + 1, e, L, R, x);
        else return kth(ls(k), s, mid, L, R, x - t);
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
};
// endregion

// region x 套 线段树
Seg<Info, Tag, 50000 * 80> seg;

struct OInfo {
    int lson, rson;
    int tid;

    OInfo() : lson(0), rson(0) {
        tid = seg.new_tree();
    }

    void init(int s, int e, int a[]) {}

    void apply(int L, int R) {
        seg.upd(tid, L, R, 1);
    }

    ll get(int L, int R) {
        return seg.qr(tid, L, R).sum;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 50010;

using ai4 = array<ll, 4>;

int n, m;
ai4 qs[N];
OSeg<OInfo, Info, Tag, N> oseg;
vector<int> lsh;
int nl;

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    for (int i = 1; i <= m; i++) lsh.push_back(get<3>(qs[i]));
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();
}

void solve() {
    init();
    oseg.init(1, nl);
    seg.init(1, n);

    for (int i = 1; i <= m; i++) {
        auto [op, a, b, c] = qs[i];

        if (op == 1) {
            c = get(c) + 1;
            oseg.upd(c, a, b);
        }
        if (op == 2) {
            cout << lsh[oseg.kth(a, b, c) - 1] << "\n";
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
        for (int i = 1; i <= m; i++) {
            ll ta, tb, tc, td;
            cin >> ta >> tb >> tc >> td;
            qs[i] = {ta, tb, tc, td};
        }

        solve();
    }

    return 0;
}