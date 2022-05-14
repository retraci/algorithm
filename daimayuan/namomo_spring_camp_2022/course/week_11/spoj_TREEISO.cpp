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
using ai3 = array<int, 3>;
mt19937 mrnd(time(0));
mt19937_64 mrnd64(time(0));

int rnd(int mod) {
    return mrnd() % mod;
}

// region 双模哈希
const int mod1 = 1e9 + 7;
const int mod2 = 1e9 + 9;

pii operator+(const pii &a, const pii &b) {
    int c1 = a.fi + b.fi, c2 = a.se + b.se;
    if (c1 >= mod1) c1 -= mod1;
    if (c2 >= mod2) c2 -= mod2;
    return {c1, c2};
}

pii operator-(const pii &a, const pii &b) {
    int c1 = a.fi - b.fi, c2 = a.se - b.se;
    if (c1 < 0) c1 += mod1;
    if (c2 < 0) c2 += mod2;
    return {c1, c2};
}

pii operator*(const pii &a, const pii &b) {
    return {1LL * a.fi * b.fi % mod1, 1LL * a.se * b.se % mod2};
}

vector<pii> pw;
pii base;

void init_hash(int lim = 0) {
    pw = vector<pii>(lim + 1);
    base = {rnd(mod1), rnd(mod2)};
    pw[0] = {1, 1};
    for (int i = 1; i <= lim; i++) pw[i] = pw[i - 1] * base;
}
// endregion

// region 树哈希
template<int N, int M>
struct Tree_hash {
    int n, is_rand;
    int h[N + 10], ne[M * 2 + 10], e[M * 2 + 10], edm;
    int sz[N + 10], rd[N + 10];
    vector<int> ctr;

    Tree_hash() {}

    void init(int _n) {
        n = _n;
        fill(h, h + n + 1, -1), edm = 0;

        if (!is_rand) {
            is_rand = 1;
            for (int i = 1; i <= N; i++) rd[i] = rnd(1e9 + 7);
        }
    }

    void add(int u, int v) {
        e[edm] = v, ne[edm] = h[u], h[u] = edm++;
    }

    void dfs1(int u, int fno) {
        sz[u] = 1;
        int mxs = 0;
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (v == fno) continue;

            dfs1(v, u);
            sz[u] += sz[v];
            mxs = max(mxs, sz[v]);
        }

        int mx = max(mxs, n - sz[u]);
        if (mx <= n / 2) ctr.push_back(u);
    }

    pii dfs2(int u, int fno) {
        sz[u] = 1;

        pii res = {1, 1};
        for (int i = h[u]; ~i; i = ne[i]) {
            int v = e[i];
            if (v == fno) continue;

            pii ha = dfs2(v, u);
            sz[u] += sz[v];

            int salt = rd[sz[v]];
            res = res + (ha * (pii) {salt, salt});
        }

        return res;
    }

    // 有根树哈希传入 root, 无根树不传
    array<pii, 2> work(int rt = 0) {
        if (rt == 0) {
            fill(sz, sz + n + 1, 0);
            ctr = {};
            dfs1(1, -1);
        } else {
            ctr = {rt};
        }

        fill(sz, sz + n + 1, 0);
        pii h1 = dfs2(ctr[0], -1);
        pii h2 = ctr.size() == 2 ? dfs2(ctr[1], -1) : (pii) {-1, -1};
        if (h1 > h2) swap(h1, h2);
        array<pii, 2> res = {h1, h2};

        return res;
    }
};
// endregion

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 100010;

int n;
pii es[2 * N];
Tree_hash<N, N> th;

void solve() {
    th.init(n);
    for (int i = 1; i <= n - 1; i++) {
        auto [u, v] = es[i];
        th.add(u, v), th.add(v, u);
    }
    auto h1 = th.work();

    th.init(n);
    for (int i = 1; i <= n - 1; i++) {
        auto [u, v] = es[n + i];
        th.add(u, v), th.add(v, u);
    }
    auto h2 = th.work();

    cout << (h1 == h2 ? "YES" : "NO") << "\n";
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
    cin >> _;
    while (_--) {
        cin >> n;
        for (int i = 1; i <= n - 1; i++) cin >> es[i].fi >> es[i].se;
        for (int i = 1; i <= n - 1; i++) cin >> es[n + i].fi >> es[n + i].se;
        solve();
    }

    return 0;
}