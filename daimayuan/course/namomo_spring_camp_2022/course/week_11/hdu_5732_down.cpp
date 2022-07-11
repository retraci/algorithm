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
// endregion

// region 树哈希
vector<int> rd;

void init_rd(int lim) {
    rd = vector<int>(lim + 1);
    for (int i = 1; i <= lim; i++) rd[i] = rnd(1e9 + 7);
}

template<int N, class G>
struct TreeHash {
    int n;
    int sz[N + 10];
    pii ha[N + 10];
    vector<int> ctr;

    TreeHash() {}

    void dfs1(int u, int fno, const G &g) {
        sz[u] = 1;
        int mxs = 0;
        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];
            if (v == fno) continue;

            dfs1(v, u, g);
            sz[u] += sz[v];
            mxs = max(mxs, sz[v]);
        }

        int mx = max(mxs, n - sz[u]);
        if (mx <= n / 2) ctr.push_back(u);
    }

    pii dfs2(int u, int fno, const G &g) {
        sz[u] = 1;

        pii res = {1, 1};
        for (int i = g.h[u]; ~i; i = g.ne[i]) {
            int v = g.e[i];
            if (v == fno) continue;

            pii hash = dfs2(v, u, g);
            sz[u] += sz[v];

            int salt = rd[sz[v]];
            res = res + (hash * (pii) {salt, salt});
        }

        return ha[u] = res;
    }

    // 有根树哈希传入 root, 无根树传-1, 返回 重心 和 重心对应的哈希
    array<pair<int, pii>, 2> work(int rt, const G &g) {
        n = g.n;
        if (rt == -1) {
            fill(sz, sz + n + 1, 0);
            ctr.clear();
            dfs1(1, -1, g);
        } else {
            ctr = {rt};
        }
        if (ctr.size() != 2) ctr.push_back(-1);

        fill(sz, sz + n + 1, 0);
        pii h1 = dfs2(ctr[0], -1, g);
        pii h2 = ctr[1] != -1 ? dfs2(ctr[1], -1, g) : (pii) {-1, -1};

        return (array<pair<int, pii>, 2>) {(pair<int, pii>) {ctr[0], h1}, (pair<int, pii>) {ctr[1], h2}};
    }
};
// endregion

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

const int dir[9][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}, {0, 0}};
const int N = 100010;

using pss = pair<string, string>;
using G = Graph<N, N>;
using node = pair<pii, int>;

int n;
pss es[2 * N];
G g[2];
TreeHash<N, G> th[2];
map<int, int> mp;
vector<string> lsh;

void dfs(int u1, int u2, int fno1, int fno2) {
    vector<node> to[2];
    for (int i = g[0].h[u1]; ~i; i = g[0].ne[i]) {
        int v = g[0].e[i];
        if (v == fno1) continue;

        to[0].push_back({th[0].ha[v], v});
    }
    for (int i = g[1].h[u2]; ~i; i = g[1].ne[i]) {
        int v = g[1].e[i];
        if (v == fno2) continue;

        to[1].push_back({th[1].ha[v], v});
    }
    sort(to[0].begin(), to[0].end());
    sort(to[1].begin(), to[1].end());

    for (int i = 0; i < to[0].size(); i++) {
        int v1 = to[0][i].se;
        int v2 = to[1][i].se;

        mp[v1] = v2;
        dfs(v1, v2, u1, u2);
    }
}

int get(const string &x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin();
}

void init() {
    lsh = {};

    for (int i = 1; i <= n - 1; i++) {
        string u = es[i].fi, v = es[i].se;
        lsh.push_back(u), lsh.push_back(v);
    }

    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
}

void solve() {
    if (n == 1) return;
    init();

    g[0].init(n, n - 1);
    for (int i = 1; i <= n - 1; i++) {
        string u = es[i].fi, v = es[i].se;

        int nu = get(u) + 1, nv = get(v) + 1;
        g[0].add(nu, nv), g[0].add(nv, nu);
    }
    g[1].init(n, n - 1);
    for (int i = 1; i <= n - 1; i++) {
        string u = es[n + i].fi, v = es[n + i].se;

        int nu = get(u) + 1, nv = get(v) + 1;
        g[1].add(nu, nv), g[1].add(nv, nu);
    }

    int rt1 = th[0].work(-1, g[0])[0].fi;
    int rt2 = th[1].work(-1, g[1])[0].fi;

    mp.clear();
    mp[rt1] = rt2;
    dfs(rt1, rt2, -1, -1);

    for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
        int ta = it->fi, tb = it->se;
        cout << lsh[ta - 1] << " " << lsh[tb - 1] << "\n";
    }
}

void prework() {
    init_rd(100000);
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
    while (cin >> n) {
        for (int i = 1; i <= n - 1; i++) {
            string u, v;
            cin >> u >> v;
            es[i] = {u, v};
        }
        for (int i = 1; i <= n - 1; i++) {
            string u, v;
            cin >> u >> v;
            es[n + i] = {u, v};
        }

        solve();
    }

    return 0;
}