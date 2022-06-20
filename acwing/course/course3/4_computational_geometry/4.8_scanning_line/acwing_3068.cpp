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
using ai4 = array<int, 4>;
mt19937 mrnd(std::random_device{}());

int rnd(int mod) {
    return mrnd() % mod;
}

// region 扫描线线段树 (矩形面积并)
using cgt = ll;

vector<cgt> lsh;
int nl;

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

    void pull(int k, int s, int e) {
        if (info[k].sum) info[k].len = lsh[e + 1] - lsh[s];
        else if (s != e) info[k].len = info[ls(k)].len + info[rs(k)].len;
        else info[k].len = 0;
    }

    void apply(int k, int s, int e, const Tag &v) {
        info[k].apply(s, e, v);
        tag[k].apply(s, e, v);
    }

    void upd(int &k, int s, int e, int L, int R, const Tag &v) {
        if (!k) k = new_node();

        if (L <= s && e <= R) {
            apply(k, s, e, v);
            pull(k, s, e);
            return;
        }

        if (L <= mid) upd(ls(k), s, mid, L, R, v);
        if (R >= mid + 1) upd(rs(k), mid + 1, e, L, R, v);
        pull(k, s, e);
    }

    void set(int &k, int s, int e, int id, const Info &v) {
        if (!k) k = new_node();

        if (s == e) {
            info[k].set(v);
            return;
        }

        if (id <= mid) set(ls(k), s, mid, id, v);
        if (id >= mid + 1) set(rs(k), mid + 1, e, id, v);
        pull(k, s, e);
    }

    void upd(int L, int R, const Tag &v) {
        if (R < L) return;
        upd(rt, lb, rb, L, R, v);
    }

    void set(int id, const Info &v) {
        set(rt, lb, rb, id, v);
    }
};
// endregion

// region 扫描线
struct Tag {
    int x;

    Tag(int x = 0) : x(x) {}

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
    int sum;
    cgt len;

    Info(int sum = 0, cgt len = 0) : lson(0), rson(0), sum(sum), len(len) {}

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
const int N = 1e5 + 10;

int n;
ai4 a[N];
Seg<Info, Tag, 2 * N> seg;

int get(int x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    for (int i = 1; i <= n; i++) {
        auto [x1, y1, x2, y2] = a[i];
        lsh.push_back(y1);
        lsh.push_back(y2);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nl = lsh.size();
}

void solve() {
    init();

    ai4 b[n * 2 + 1];
    for (int i = 1; i <= n; i++) {
        auto [x1, y1, x2, y2] = a[i];
        b[2 * i - 1] = {x1, y1, y2, 1};
        b[2 * i] = {x2, y1, y2, -1};
    }

    sort(b + 1, b + 2 * n + 1, [](auto &a, auto &b) {
        return a[0] < b[0];
    });

    ll ans = 0;
    seg.init(0, nl - 2);
    for (int i = 1; i <= 2 * n; i++) {
        auto [x, y1, y2, v] = b[i];

        if (i - 1 >= 1) {
            ll dx = b[i][0] - b[i - 1][0];
            ans += dx * seg.info[1].len;
        }

        int L = get(y1), R = get(y2) - 1;
        seg.upd(L, R, v);
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
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < 4; j++) cin >> a[i][j];
        }
        solve();
    }

    return 0;
}