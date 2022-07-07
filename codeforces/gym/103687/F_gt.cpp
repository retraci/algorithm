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
mt19937 mrnd(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

// region fenwick
template<int SZ>
struct Fenwick {
    using fwt = int;

    int n;
    fwt tr[SZ + 10];

    Fenwick() {}

    void init(int _n) {
        n = _n;
        fill(tr, tr + n + 1, 0);
    }

    void upd(int id, fwt x) {
        assert(id > 0);
        for (int i = id; i <= n; i += i & -i) tr[i] = tr[i] + x;
    }

    fwt qr(int id) {
        fwt res = 0;
        for (int i = id; i; i -= i & -i) res = res + tr[i];
        return res;
    }

    int kth(fwt x) {
        int pos = 0;
        for (int i = __lg(n); i >= 0; i--) {
            if (pos + (1 << i) <= n && tr[pos + (1 << i)] < x) {
                pos += 1 << i;
                x -= tr[pos];
            }
        }

        return pos + 1;
    }
};
// endregion

// region 二维数点
template<int Q, class Fenwick>
struct TwoDimCount {
    using fwt = int;
    using tdct = int;
    using at3 = array<tdct, 3>;
    using at4 = array<tdct, 4>;
    using at5 = array<tdct, 5>;

    int oq;
    at4 oqs[4 * Q + 10];

    TwoDimCount() {}

    // ps[i] = {x, y, w}
    // qs[i] = {qid, x1, x2, y1, y2}
    // m 为第二维的值域, q 为询问总个数
    vector<fwt> work(vector<at3> ps, const vector<at5> &qs, Fenwick &fw, int m, int q) {
        oq = 0;
        for (auto [qid, x1, x2, y1, y2] : qs) {
            oqs[++oq] = {qid, x1 - 1, y2, -1};
            oqs[++oq] = {qid, x1 - 1, y1 - 1, +1};
            oqs[++oq] = {qid, x2, y2, +1};
            oqs[++oq] = {qid, x2, y1 - 1, -1};
        }

        sort(ps.begin(), ps.end(), [](auto &lhs, auto &rhs) {
            return lhs[0] < rhs[0];
        });
        sort(oqs + 1, oqs + oq + 1, [](auto &lhs, auto &rhs) {
            return lhs[1] < rhs[1];
        });

        fw.init(m);
        int u = 0;
        vector<fwt> res(q + 1);
        for (int i = 1; i <= oq; i++) {
            auto [qid, x, y, sgn] = oqs[i];

            while (u < ps.size() && ps[u][0] <= x) fw.upd(ps[u][1], ps[u][2]), u++;
            res[qid] += sgn * fw.qr(y);
        }
        return res;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 100010;
const int Q = 200010;

using ai5 = array<int, 5>;

int n, q;
int a[N];
pii qs[Q];
TwoDimCount<Q, Fenwick<N>> tdc;
Fenwick<N> fw1, fw2;
int A[N], B[N];

void solve() {
    ll cur = 0;
    fw1.init(n);
    for (int i = 1; i <= n; i++) {
        A[i] = fw1.qr(a[i]);
        B[i] = a[i] - 1 - A[i];
        cur += min(A[i], B[i]);
        fw1.upd(a[i], 1);
    }

    vector<ai3> ps[8];
    for (int i = 1; i <= n; i++) {
        if (A[i] == B[i]) ps[1].push_back({i, a[i], 1});
        if (A[i] + 1 == B[i]) ps[2].push_back({i, a[i], 1});
        if (B[i] + 1 == A[i]) ps[3].push_back({i, a[i], 1});
        if (A[i] + 2 <= B[i]) ps[4].push_back({i, a[i], 1});
        if (B[i] + 2 <= A[i]) ps[5].push_back({i, a[i], 1});

        ps[6].push_back({i, a[i], 1});
        ps[7].push_back({i, a[i], 1});
    }

    vector<ai5> tdcqs[8];
    for (int i = 1; i <= q; i++) {
        auto [u, v] = qs[i];

        int mi = min(a[u], a[v]), mx = max(a[u], a[v]);
        if (u + 1 <= v - 1) {
            for (int k = 1; k <= 5; k++) tdcqs[k].push_back({i, u + 1, v - 1, mi, mx});
        }
        tdcqs[6].push_back({i, 1, u - 1, 1, a[v] - 1});
        tdcqs[7].push_back({i, 1, v, 1, a[u] - 1});
    }

    vector<int> ret[8];
    for (int i = 1; i <= 7; i++) ret[i] = tdc.work(ps[i], tdcqs[i], fw2, n, q);

    for (int i = 1; i <= q; i++) {
        auto [u, v] = qs[i];

        ll ans = cur - min(A[u], B[u]) - min(A[v], B[v]);
        int t1 = min(ret[6][i], a[v] - 1 - ret[6][i]);
        int t2 = min(ret[7][i], a[u] - 1 - ret[7][i]);
        ans += t1 + t2;
        if (a[u] < a[v]) {
            ans += -ret[1][i] - ret[2][i] - ret[4][i] + ret[5][i];
        } else {
            ans += -ret[1][i] - ret[3][i] + ret[4][i] - ret[5][i];
        }

        cout << ans << "\n";
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
        for (int i = 1; i <= n; i++) cin >> a[i];
        cin >> q;
        for (int i = 1; i <= q; i++) {
            int u, v;
            cin >> u >> v;
            if (u > v) swap(u, v);
            qs[i] = {u, v};
        }
        solve();
    }

    return 0;
}