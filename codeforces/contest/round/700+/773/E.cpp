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
using ai4 = array<int, 4>;

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

// region 区间最大值
struct Tag {
    ll x;

    Tag(ll x = -1) : x(x) {}

    bool check() const {
        return x != -1;
    }

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        x = max(x, a.x);
    }
};

struct Info {
    int lson, rson;
    ll sum;

    Info(ll sum = 1e9) : lson(0), rson(0), sum(sum) {}

    void apply(int s, int e, const Tag &a) {
        if (!a.check()) return;
        sum = a.x;
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
const int N = 2e5 + 10;

int n, m;
ai4 qs[N];
Seg<Info, Tag, N> seg;

void solve() {
    seg.init(1, n);

    vector<int> mit(n + 1, 1e9);
    set<int> st;
    st.insert(1e9);
    for (int i = 1; i <= n; i++) st.insert(i);
    for (int i = 1; i <= m; i++) {
        auto [op, L, R, x] = qs[i];
        if (op == 1) continue;

        if (x == 0) {
            auto it = st.lower_bound(L);
            while (*it <= R) {
                seg.upd(*it, i);
                mit[*it] = i;
                it = st.erase(it);
            }
        }
    }

    unordered_set<int> b;
    vector<int> bqs[n + 1];
    for (int i = 1; i <= m; i++) {
        auto [op, L, R, x] = qs[i];
        if (op == 1) continue;

        if (x == 1) {
            auto it1 = st.lower_bound(L);
            auto it2 = next(it1);
            if (*it2 > R) {
                bqs[*it1].push_back(i);
                if (!b.count(*it1)) {
                    b.insert(*it1);
                    seg.upd(*it1, 0);
                }
            }
        }
    }

    for (int pr : b) {
        for (int qid : bqs[pr]) {
            auto [op, L, R, x] = qs[qid];
            int t = max(qid, (int) seg.qr(L, R).sum);
            mit[pr] = min(mit[pr], t);
        }
    }

    for (int i = 1; i <= m; i++) {
        auto [op, L, R, x] = qs[i];
        if (op == 0) continue;

        if (!st.count(x)) {
            if (mit[x] <= i) cout << "NO" << "\n";
            else cout << "N/A" << "\n";
        } else {
            if (mit[x] <= i) cout << "YES" << "\n";
            else cout << "N/A" << "\n";
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
            int op, L, R, x;
            cin >> op;
            if (op == 0) cin >> L >> R >> x;
            else cin >> x;
            qs[i] = {op, L, R, x};
        }

        solve();
    }

    return 0;
}