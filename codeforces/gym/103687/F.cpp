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

// region 二位数点 fenwick
template<int SZ>
struct Fenwick {
    using fwt = int;
    using ptt = pair<fwt, fwt>;
    using at4 = array<fwt, 4>;

    int n, q;
    fwt tr[SZ + 10];
    vector<ptt> ps;
    vector<at4> qs;

    Fenwick() {}

    void init(int _n, int _q) {
        n = _n, q = _q;
        fill(tr, tr + n + 1, 0);
        ps.clear(), qs.clear();
    }

    void upd(int id, fwt x) {
        for (int i = id; i <= n; i += i & -i) tr[i] = tr[i] + x;
    }

    fwt qr(int id) {
        fwt res = 0;
        for (int i = id; i; i -= i & -i) res = res + tr[i];
        return res;
    }

    void add_point(int x, fwt y) {
        ps.push_back({x, y});
    }

    // qid, 左, 右, 下, 上
    void add_qr(int qid, int x1, int x2, fwt y1, fwt y2) {
        qs.push_back({qid, x1 - 1, y2, -1});
        qs.push_back({qid, x1 - 1, y1 - 1, +1});
        qs.push_back({qid, x2, y2, +1});
        qs.push_back({qid, x2, y1 - 1, -1});
    }

    vector<fwt> get_ans() {
        sort(ps.begin(), ps.end(), [](auto &a, auto &b) {
            return a.fi < b.fi;
        });
        sort(qs.begin(), qs.end(), [](auto &a, auto &b) {
            return a[1] < b[1];
        });

        int u = 0;
        vector<fwt> ans(q + 1);
        for (auto [qid, x, y, sgn] : qs) {
            while (u < ps.size() && ps[u].fi <= x) upd(ps[u].se, 1), u++;
            ans[qid] += sgn * qr(y);
        }
        return ans;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 100010;
const int Q = 200010;

int n, q;
int a[N];
pii qs[Q];
Fenwick<N> fw[8];
int A[N], B[N];

void solve() {
    ll cur = 0;
    fw[0].init(n, q);
    for (int i = 1; i <= n; i++) {
        A[i] = fw[0].qr(a[i]);
        B[i] = a[i] - 1 - A[i];
        cur += min(A[i], B[i]);
        fw[0].upd(a[i], 1);
    }

    for (int i = 1; i <= 7; i++) fw[i].init(n, q);
    for (int i = 1; i <= n; i++) {
        if (A[i] == B[i]) fw[1].add_point(i, a[i]);
        if (A[i] + 1 == B[i]) fw[2].add_point(i, a[i]);
        if (B[i] + 1 == A[i]) fw[3].add_point(i, a[i]);
        if (A[i] + 2 <= B[i]) fw[4].add_point(i, a[i]);
        if (B[i] + 2 <= A[i]) fw[5].add_point(i, a[i]);

        fw[6].add_point(i, a[i]);
        fw[7].add_point(i, a[i]);
    }

    for (int i = 1; i <= q; i++) {
        auto [u, v] = qs[i];

        int mi = min(a[u], a[v]), mx = max(a[u], a[v]);
        if (u + 1 <= v - 1) {
            for (int k = 1; k <= 5; k++) fw[k].add_qr(i, u + 1, v - 1, mi, mx);
        }
        fw[6].add_qr(i, 1, u - 1, 1, a[v] - 1);
        fw[7].add_qr(i, 1, v, 1, a[u] - 1);
    }

    vector<vector<int>> ret(8);
    for (int i = 1; i <= 7; i++) ret[i] = fw[i].get_ans();

    for (int i = 1; i <= q; i++) {
        auto [u, v] = qs[i];

//        for (int k = 1; k <= 7; k++) {
//            cout << ret[k][i] << " ";
//        }
//        cout << "\n";

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