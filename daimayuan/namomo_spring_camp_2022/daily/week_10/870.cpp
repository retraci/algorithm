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
        class Merge = std::plus<Info>>
struct Seg {
#define mid (s + e >> 1)
#define ls(x) (info[x].lson)
#define rs(x) (info[x].rson)

    const Merge merge;
    int lb, rb, rt, mem;
    Info info[SZ * 4];
    Tag tag[SZ * 4];

    Seg() : merge(Merge()) {
        init(1, SZ);
    }

    void init(int L, int R) {
        rt = 0, mem = 0, lb = L, rb = R;
        info[0] = Info();
        tag[0] = Tag();
    }

    int new_node() {
        int id = ++mem;
        info[id] = Info();
        tag[id] = Tag();
        return id;
    }

    void pull(int k) {
        info[k].set(merge(info[ls(k)], info[rs(k)]));
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
        return merge(qr(ls(k), s, mid, L, R), qr(rs(k), mid + 1, e, L, R));
    }

    int qr_kth(int k, int s, int e, ll x) {
        if (s == e) return x <= info[k].sum ? s : rb + 1;

        push(k, s, e);
        if (x <= info[ls(k)].sum) return qr_kth(ls(k), s, mid, x);
        else return qr_kth(rs(k), mid + 1, e, x - info[ls(k)].sum);
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

    int qr_kth(ll x) {
        return qr_kth(rt, lb, rb, x);
    }
};
// endregion

// region 区间最大值
struct Tag {
    ll x;
    Tag(ll x = 0) : x(x) {}

    bool check() const {
        return x != 0;
    }

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        x = max(x, a.x);
    }
};

struct Info {
    int lson, rson;
    ll sum;
    Info(ll sum = 0) : lson(0), rson(0), sum(sum) {}

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        sum = max(sum, a.x);
    }

    friend Info operator+(const Info &a, const Info &b) {
        return max(a.sum, b.sum);
    }

    void set(const Info &a) {
        sum = a.sum;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 1e5 + 10;

int n;
int a[N];
Seg<Info, Tag, N> seg;

void solve() {
    vector<int> L(n + 1), R(n + 1);
    {
        int lst = 0, cur = 0;
        for (int i = 2; i <= n - 1; i++) {
            if (a[i] != -1 && lst && a[lst] > a[i]) cur = lst;
            L[i] = cur;
            if (a[i] != -1) lst = i;
        }
    }
    {
        int lst = 0, cur = n + 1;
        for (int i = n - 1; i >= 2; i--) {
            if (a[i] != -1 && lst && a[lst] > a[i]) cur = lst;
            R[i] = cur;
            if (a[i] != -1) lst = i;
        }
    }

    seg.init(1, n);
    for (int i = 2; i <= n - 1; i++) {
        int lb = L[i], rb = R[i];
//        debug(i, lb, rb);

        seg.upd(lb + 1, i - 1, rb - 1);
    }

    vector<int> ans;
    for (int k = 3; k <= n; k++) {
        int rem = n % k;
        if (rem == 1 || rem == 2) continue;

        int flag = 0;
        for (int i = 1; i <= n; i += k) {
            int lb = i, rb = min(n, i + k - 1);
            int mx = seg.qr(lb, lb).sum;
            if (mx < rb) flag = 1;
        }

//        debug(k, flag);
        if (!flag) ans.push_back(k);
    }

    cout << ans.size() << "\n";
    for (int x : ans) cout << x << "\n";
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