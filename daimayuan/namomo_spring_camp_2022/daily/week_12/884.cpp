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
#include <cassert>
#include <random>
#include <cmath>

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
using pll = pair<ll, ll>;
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

const int MOD = 1e9 + 7;

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

    void pull(int k) {
        info[k].set(plus(info[ls(k)], info[rs(k)]));
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
        pull(k);
    }

    void set(int &k, int s, int e, int id, const Info &v) {
        if (!k) k = new_node();

        if (s == e) {
            info[k].set(v);
            return;
        }

        if (id <= mid) set(ls(k), s, mid, id, v);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, v);
        pull(k);
    }

    Info qr(int k, int s, int e, int L, int R) {
        if (L <= s && e <= R) return info[k];

        if (R <= mid) return qr(ls(k), s, mid, L, R);
        if (L >= mid + 1) return qr(rs(k), mid + 1, e, L, R);
        return plus(qr(ls(k), s, mid, L, R), qr(rs(k), mid + 1, e, L, R));
    }

    int kth(int k, int s, int e, ll x) {
        if (s == e) return s;

        if (x <= info[ls(k)].sum) return kth(ls(k), s, mid, x);
        else return kth(rs(k), mid + 1, e, x - info[ls(k)].sum);
    }

    void upd(int id, const Tag &v) {
        upd(rt, lb, rb, id, v);
    }

    void set(int id, const Info &v) {
        set(rt, lb, rb, id, v);
    }

    Info qr(int L, int R) {
        if (R < L) return Info();
        return qr(rt, lb, rb, L, R);
    }

    int kth(ll x) {
        return kth(rt, lb, rb, x);
    }
};
// endregion

// region 区修, 维护最大值
struct Tag {
    int len, cnt;

    Tag(int len = -1, int cnt = 0) : len(len), cnt(cnt) {}

    bool check() const {
        return len != -1;
    }

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
    }
};

struct Info {
    int lson, rson;
    int len, cnt;

    Info(int len = 0, int cnt = 1) : lson(0), rson(0), len(len), cnt(cnt) {}

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        if (len != a.len) {
            if (len < a.len) len = a.len, cnt = a.cnt;
        } else {
            cnt += a.cnt;
            cnt %= MOD;
        }
    }

    friend Info operator+(const Info &a, const Info &b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        if (a.len != b.len) {
            if (a.len > b.len) return a;
            else return b;
        } else {
            int sum = (a.cnt + b.cnt) % MOD;
            return {a.len, sum};
        }
    }

    void set(const Info &a) {
        len = a.len;
        cnt = a.cnt;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 4e5 + 10;

int n;
int a[N];
vector<int> lsh;
int nl;
Seg<Info, Tag, N> seg;

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    lsh = {};
    for (int i = 1; i <= n; i++) lsh.push_back(a[i]);
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();

    for (int i = 1; i <= n; i++) a[i] = get(a[i]) + 1;
}

void solve() {
    init();
    seg.init(1, n);

    vector<pii> f(n + 1);
    for (int i = 1; i <= n; i++) {
        auto t = seg.qr(1, a[i] - 1);

        f[i] = {t.len + 1, t.cnt};
        seg.upd(a[i], {f[i].fi, f[i].se});
    }

    auto [mxl, _] = *max_element(f.begin() + 1, f.end());
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (mxl == f[i].fi) {
            ans += f[i].se;
            ans %= MOD;
        }
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
        cin >> n;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}