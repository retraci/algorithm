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
mt19937 mrnd(chrono::steady_clock::now().time_since_epoch().count());

int rnd(int mod) {
    return mrnd() % mod;
}

// region 区修线段树
template<class Info, class Tag, int SZ,
        class Plus = std::plus<Info>>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)

    const Plus plus;
    int lb, rb, rt, mem;
    Info info[SZ * 4];
    Tag tag[SZ * 4];

    Seg() : plus(Plus()) {}

    void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        info[0] = Info();
        tag[0] = Tag();
    }

    int new_node() {
        int id = ++mem;
        assert(id < SZ * 4);
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
        if (info[ls(k)].sum >= x) return kth(ls(k), s, mid, x);
        else return kth(rs(k), mid + 1, e, x - info[ls(k)].sum);
    }

    void upd(int L, int R, const Tag &v) {
        if (R < L) return;
        upd(rt, lb, rb, L, R, v);
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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 3e5 + 10;

int n, k;
ll a[N];
Seg<Info, Tag, N> seg;

void solve() {
    seg.init(1, n + 1);
    for (int i = 1; i <= n; i++) seg.set(i, a[i] - a[i - 1]);

    ll ans = 0;
    for (int i = n; i >= 1; i--) {
        ll x = seg.qr(1, i).sum;
        if (x > 0) {
            int L = max(1, i - k + 1), R = L + k - 1;
            ll y = i - L + 1;
            ll c = (x + y - 1) / y;

            ll d = -c;
            ll s = d, t = s + d * (k - 1);
            seg.upd(L, L, s), seg.upd(L + 1, R, d), seg.upd(R + 1, R + 1, -t);
            ans += c;
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
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> a[i];
        solve();
    }

    return 0;
}