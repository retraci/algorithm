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

// region 无权图
template<int N, int M>
struct Graph {
    int n, m;
    int h[N + 10], ne[M * 2 + 10], e[M * 2 + 10], edm;

    Graph() {}

    void init(int _n, int _m) {
        n = _n, m = _m;
        fill(h, h + n + 1, -1), edm = 0;
    }

    void add(int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }
};
// endregion

// region 区间修改 fenwick
template<int SZ>
struct Fenwick {
    using fwt = ll;

    int n;
    fwt tr1[SZ + 10], tr2[SZ + 10];

    Fenwick() {}

    void init(int _n) {
        n = _n;
        fill(tr1, tr1 + n + 1, 0);
        fill(tr2, tr2 + n + 1, 0);
    }

    void upd(fwt tr[], int id, fwt x) {
        assert(id > 0);
        for (int i = id; i <= n; i += i & -i) tr[i] = tr[i] + x;
    }

    fwt qr(fwt tr[], int id) {
        fwt res = 0;
        for (int i = id; i; i -= i & -i) res = res + tr[i];
        return res;
    }

    fwt get_presum(int id) {
        return (id + 1) * qr(tr1, id) - qr(tr2, id);
    }

    void upd_range(int L, int R, fwt x) {
        upd(tr1, L, x), upd(tr1, R + 1, -x);
        upd(tr2, L, x * L), upd(tr2, R + 1, -x * (R + 1));
    }

    fwt qr_range(int L, int R) {
        return get_presum(R) - get_presum(L - 1);
    }
};
// endregion

const int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int N = 1e6 + 10;

int n, q, rt;
int a[N];
Graph<N, N> g;
Fenwick<N> fw;
int in[N], out[N], id[N], ti;

void pdfs(int u, int fno) {
    id[++ti] = u, in[u] = ti;

    for (int i = g.h[u]; ~i; i = g.ne[i]) {
        int v = g.e[i];
        if (v == fno) continue;

        pdfs(v, u);
    }

    out[u] = ti;
}

void solve() {
    pdfs(rt, -1);

    fw.init(n);
    for (int i = 1; i <= n; i++) fw.upd_range(i, i, a[id[i]]);

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int u, x;
            cin >> u >> x;

            fw.upd_range(in[u], out[u], x);
        }
        if (op == 2) {
            int u;
            cin >> u;

            cout << fw.qr_range(in[u], out[u]) << "\n";
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
        cin >> n >> q >> rt;
        for (int i = 1; i <= n; i++) cin >> a[i];
        g.init(n, -1);
        for (int i = 1; i <= n - 1; i++) {
            int u, v;
            cin >> u >> v;
            g.add(u, v);
            g.add(v, u);
        }
        solve();
    }

    return 0;
}