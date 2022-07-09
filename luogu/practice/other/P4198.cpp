#include <bits/stdc++.h>

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
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

struct node {
    int x, y;

    node(int x, int y) : x(x), y(y) {}

    bool operator<=(const node &rhs) const {
        auto [x2, y2] = rhs;

        return 1LL * y * x2 <= 1LL * y2 * x;
    }

    bool operator<(const node &rhs) const {
        auto [x2, y2] = rhs;

        return 1LL * y * x2 < 1LL * y2 * x;
    }

    bool operator!=(const node &rhs) const {
        auto [x2, y2] = rhs;

        return x != x2 || y != y2;
    }
};

// region 单点修改线段树
template<class Info, class Tag, int SZ,
        class Plus = std::plus<Info>>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)

    const Plus plus;
    int lb, rb, rt, mem;
    Info info[SZ * 4];

    Seg() : plus(Plus()) {}

    void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        info[0] = Info();
    }

    int new_node() {
        int id = ++mem;
        assert(id < SZ * 4);
        info[id] = Info();
        return id;
    }

    int get(int k, int s, int e, node &lmx) {
        if (info[k].mx <= lmx) return 0;
        if (s == e) return info[k].sum;

        if (info[ls(k)].mx <= lmx) return get(rs(k), mid + 1, e, lmx);
        else return get(ls(k), s, mid, lmx) + info[k].sum - info[ls(k)].sum;
    }

    void pull(int k, int s, int e) {
        Info tar;
        tar.mx = max(info[ls(k)].mx, info[rs(k)].mx);
        tar.sum = info[ls(k)].sum + get(rs(k), mid + 1, e, info[ls(k)].mx);

        info[k].set(tar);
    }

    void apply(int k, int s, int e, const Tag &v) {
        info[k].apply(s, e, v);
    }

    void upd(int &k, int s, int e, int id, const Tag &v) {
        if (!k) k = new_node();

        if (s == e) {
            apply(k, s, e, v);
            return;
        }

        if (id <= mid) upd(ls(k), s, mid, id, v);
        if (id >= mid + 1) upd(rs(k), mid + 1, e, id, v);
        pull(k, s, e);
    }

    Info qr(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return info[k];

        if (R <= mid) return qr(ls(k), s, mid, L, R);
        if (L >= mid + 1) return qr(rs(k), mid + 1, e, L, R);
        return plus(qr(ls(k), s, mid, L, R), qr(rs(k), mid + 1, e, L, R));
    }

    void upd(int id, const Tag &v) {
        upd(rt, lb, rb, id, v);
    }

    Info qr(int L, int R) {
        if (R < L) return Info();
        return qr(rt, lb, rb, L, R);
    }
};
// endregion

// region 区间求和
struct Tag {
    node x;

    Tag(node x = {1, 0}) : x(x) {}

    bool check() const {
        return x != (node) {1, 0};
    }

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        x = a.x;
    }
};

struct Info {
    int lson, rson;
    int sum;
    node mx;

    Info(int sum = 0, node mx = {1, 0}) : lson(0), rson(0), sum(sum), mx(mx) {}

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        sum = 1;
        mx = a.x;
    }

    friend Info operator+(const Info &a, const Info &b) {
        assert(false);
        return {};
    }

    void set(const Info &a) {
        sum = a.sum;
        mx = a.mx;
    }
};
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 1e5 + 10;

int n, q;
Seg<Info, Tag, N> seg;

void solve() {
    seg.init(1, n);

    while (q--) {
        int x, y;
        cin >> x >> y;

        seg.upd(x, {{x, y}});

        cout << seg.qr(1, n).sum << "\n";
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
        cin >> n >> q;
        solve();
    }

    return 0;
}